/*
 * Programmer:  Gregory N. Schmit
 * Section:     4
 * Date:        20160304
 * Program:     Rectangular to Polar Convertor
 * Description: Simple convertor from rectanular coordinates to polar (2D) with 
 *              displaying angle in degrees for no reason.
 */

#include <iostream>
#include <math.h>
using namespace std;

const int MAX_PAIRS = 100;
const double EPSILON = .00001;
const double SHIFT_VERT = 6;
const double SHIFT_HORIZ = 2;

double pol_r(double x, double y)
/*
 * PRE: input double x and y, elements of REAL
 *      include math.h
 * PST: FCTVAL == sqrt(x^2 + y^2)
 */
{
        return sqrt(pow(x,2.0)+pow(y,2.0));
        // sqrt is faster than pow(z,0.5)
}

double pol_theta(double x, double y)
/*
 * PRE: input double x and y, elements of REAL
 *      include math.h
 * PST: FCTVAL == arctan(y/x) in radians, because I write functions for adults
 *      note adjustment for cases where x is negative
 */
{
        if (x < 0)
        {
                return atan(y/x) + M_PI;
        }
        else if (x == 0)
        {
                if (y < 0) { return 3.0*M_PI/2.0; }
                else if (y > 0) { return M_PI/2.0; }
                else { return 0; }
        }
        else
        {
                return atan(y/x);
        }
}

bool double_equal(double val, double target, double epsilon)
/*
 * PRE:  input doubles for value, target, and positive epsilon
 * POST: FCTVAL = true if val is within epsilon of target
 */
{
        bool test = 0;
        if (val <= (target + epsilon) && val >= (target - epsilon)) {test = 1;}
        return test;
}

int main()
{
        // Definitions
        double inx[MAX_PAIRS];
        double iny[MAX_PAIRS];
        double x[MAX_PAIRS];
        double y[MAX_PAIRS];
        int cur = 0;
        double r[MAX_PAIRS];
        double theta[MAX_PAIRS];

        // Input
        do
        {
                cout << "Enter a pair of positive x, then y coordinates,"
                        " separated by spaces, or '0 0' to stop: ";
                cin >> inx[cur] >> iny[cur];
                x[cur] = inx[cur];
                y[cur] = iny[cur];
                cur++;
        } while (((double_equal(inx[cur-1],0,EPSILON)
                && double_equal(iny[cur-1],0,EPSILON)) == 0)
                && cur < MAX_PAIRS);
        if (double_equal(inx[cur-1],0,EPSILON)
                && double_equal(iny[cur-1],0,EPSILON))
        {
                cur--;
        }

        // Process
        for (int i = 0; i < cur; i++)
        {
                x[i]+=SHIFT_HORIZ;
                y[i]+=SHIFT_VERT;
                r[i] = pol_r(x[i], y[i]);
                theta[i] = pol_theta(x[i], y[i]);
        }

        // Output
        cout << endl << "Coordinates [inputs ---> polar]:" << endl << 
                "================================" << endl;
        for (int i = 0; i < cur; i++)
        {
                cout << "(" << inx[i] << ", " << iny[i] << ") ---> (" << r[i] << 
                        ", " << theta[i]*180.0/M_PI << ")" << endl;
        }

        return 0;
}
