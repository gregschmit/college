/*
 * Programmer:  Gregory N. Schmit
 * Section:     4
 * Program:     findroot
 * Date:        20160229
 * Description: Partial implementation of Bisection method of solving for 
 *              zero(es) of a function.
 *
 *      This is modified from the original by Doug Hogan at:
 *        https://www2.cs.uic.edu/~hogand/cs107/bisection/starter-code.cpp
 *      Cleaned up with astyle --style=knf --indent=spaces=8 -xC80
 *      Comments corrected to not be on same lines as the commands.
 */

// These 11 lines are the header comments of the original program:
// Programmer:  Doug Hogan
// Section:     N/A
// Program:     Partial Solution to Bisection Code
// Date:        Last Modified 2/28/2016
// Description: This program is a partial implementation of Bisection Method,
//               Algorithm 2.1, p. 49, Burden/Faires Numerical Analysis text
//
//               Goal: Find a solution to f(x) = 0 given continuous function f
//               on interval [a,b], where f(a) and f(b) have opposite signs
//
//          Example function used: f(x) = x^3 + 4x^2 - 10 = 0; root in [1, 2]


#include <iostream>
#include <math.h>
using namespace std;

const double TOLERANCE = 0.0001;
// maximum amount of error allowed in an approximation
const int MAX_ITERATIONS = 20;
// maximum number of iterations to allow

/* gns: prototypes */
double f(double x);
double RootByBisection(double a, double b);
double Midpoint(double left, double right);
bool IsRootAccepted(double x, double leftPt, double rightPt);
void ResetEndpoints(double midpoint, double& leftPt, double& rightPt);

int main()
{
        double zero;
        // x location where root to example function is found

        zero = RootByBisection(-3.0, -1.0);

        cout << endl << "Root found at: " << zero << endl;

        return 0;
}


double f(double x)
// function whose root we'll find
// PRE:  Assigned(x)
// POST: FCTVAL == f(x) = x^3 + 4*x^2 - 10
{
        return 2.0*pow(x, 4) + 3*pow(x, 3) + x - 7.0;
}


double RootByBisection(double a, double b)
// PRE:  function f is defined && f is continuous on [a, b] &&
//       f(a) and f(b) have opposite signs
// POST: FCTVAL == x s.t. f(x) is approximately 0 within error bound
//       of TOLERANCE.
//       Method has also displayed status reports to screen.
//       If root is not found in MAX_ITERATIONS trials, FCTVAL == 99999999 and
//       and error message is displayed.
{
        double midpt;
        // midpoint of interval [a,b]
        double left;
        // left endpoint of interval being checked
        double right;
        // right endpoint of interval being checked
        int i;
        // number of iterations completed
        bool isRootAccepted;
        // flag that is true when root is within tolerance
        double result;
        // accepted root

        left = a;
        // interval endpoints initially come from parameters
        right = b;

        isRootAccepted = false;
        // initially, root is not accepted

        i = 0;
        // initially, we've done nothing

        do
                // iterate until we get acceptable root
        {
                midpt = Midpoint(left, right);
                // compute midpoint

                cout << "Trial " << i+1 << ": "
                     << "[" << left << ", " << right
                     << "]; midpt: " << midpt
                     << "; f(midpt) = " << f(midpt) << endl;
                // status report

                if(IsRootAccepted(midpt, left, right))
                        // check if this midpoint is an acceptable
                {
                        //  zero to function f
                        result = midpt;
                        // if so, return it and quit
                        isRootAccepted = true;
                } else
                        // otherwise reset interval
                {
                        // (else not needed, but for clarity)
                        // ASSERT: either left, midpt have opposite signs
                        //             or midpt, right have opposite signs

                        ResetEndpoints(midpt, left, right);
                        // adjust endpoints so next iteration

                        // uses interval where f crosses x-axis

                        i++;
                        // count the trial
                }

        } while(i < MAX_ITERATIONS && !isRootAccepted);

        if(isRootAccepted)
                // found a root
        {
                return result;
        } else
                // gave up
        {
                cout << "Root not found in "
                     << MAX_ITERATIONS << " trials." << endl;
                return 99999999;
                // error value
        }

        // NOTE: This function blurs process and output, for educational
        // purposes. In general you should not do that; you should instead just
        // do the computation and save reporting of results to the calling
        // method. Part of this is also learning the bisection algorithm.
}


double Midpoint(double left, double right)
// PRE:  Assigned(left) && Assigned(right)
// POST: FCTVAL == midpoint between left and right
{
        return (left+right)/2;
}


bool IsRootAccepted(double x, double leftPt, double rightPt)
// PRE:  Assigned(x) && leftPt < rightPt,
//       function f is defined and continuous on [leftPt, rightPt]
// POST: FCTVAL == true, if f(x) == 0
//       or width of interval [leftPt, rightPt] is less than TOLERANCE false,
//       otherwise
{
        if((f(x) == 0) ||
            // approximation gives a zero
            ((rightPt-leftPt)/2 < TOLERANCE))
                // width of interval is "small enough"
        {
                return true;
        }

        return false;
        // if we get here, approximation was
        // not close enough
}

void ResetEndpoints(double midpoint, double& leftPt, double& rightPt)
{
// PRE:  Assigned(midpoint) && leftPt < rightPt,
//       function f is defined and continuous on [leftPt, rightPt], 
//       and IsRootAccepted(x, leftPt, rightPt) == false,
//           thus exactly one of these cases is true:
//              1. f(midpoint) and f(leftPt) have different signs
//              2. f(midpoint) and f(rightPt) have different signs
// POST: leftPt or rightPt is reset to the midpoint for whichever case, 1 or 2,
//       is true, thus we have a smaller interval for the next iteration of 
//       root finding by bisection on which the Intermediate Value Theorem
//       guarantees a solution

        if (f(leftPt)*f(midpoint) < 0)
        {
                rightPt = midpoint;
        }
        else if (f(rightPt)*f(midpoint) < 0)
        {
                leftPt = midpoint;
        }
        // else if the midpoint is the same sign as both endpoints, do nothing.

}
