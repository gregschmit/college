/*
 * Programmer:  Gregory N. Schmit
 * Section:     4
 * Date:        20160313
 * Program:     Rectangular to Polar Convertor Part B
 * Description: Simple convertor from rectangular coordinates to polar (2D).
 *              Part B: getting data from files.
 *
 *              Original code written in KNF style, but submitted version 
 *              modified from 8-space indents to 4-space indents to satify 
 *              arbitrary class indent length requirements. Braces are in KNF.
 */

#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
using namespace std;

const int MAX_PAIRS = 1000;                     /* max pairs of data (not 0!) */
const double EPSILON = .00001;                  /* tolerance of checking double 
                                                   vals for equiv. to int */
const double SHIFT_VERT = 6;                    /* vertical shift (if any) */
const double SHIFT_HORIZ = 2;                   /* horizontal shift (if any) */
const string FILENAME_IN = "inputs.dat";        /* input file */
const string FILENAME_OUT = "outputs.dat";      /* output file */
const bool SHOW_USER_CONTENT = 1;               /* display any console out */
const bool SHOW_USER_OUTPUT = 1;                /* display final data output */

void rect_to_polar(double x, double y, double & r, double & theta)
/*
 * PRE: input double x and y, elements of REAL
 *      input double r and theta by reference, elements of REAL
 *      include math.h
 * PST: output r and theta as double
 *      theta is arctan(y/x) in radians, because I write methods for adults.
 *      modifications for arctan to account for negative x and y values, and 
 *      zeroes for x or y.
 */
{
        r = sqrt(pow(x,2.0)+pow(y,2.0));
        if (x < 0) {
                theta = atan(y/x) + M_PI;
        } else if (x == 0) {
                if (y < 0) { theta = 3.0*M_PI/2.0; }
                else if (y > 0) { theta = M_PI/2.0; }
                else { theta = 0; }
        } else {
                theta = atan(y/x);
        }
        return;
}

bool double_equal(double val, double target, double epsilon)
/*
 * PRE:  input doubles for value, target, and positive epsilon
 * PST:  FCTVAL = true if val is within (inclusive) epsilon of target
 */
{
        bool test = 0;
        if (val <= (target + epsilon) && val >= (target - epsilon)) {
                test = 1;
        }
        return test;
}

int main()
/*
 * PRE: input data in FILENAME_IN (see global constants) where on each line 
 *      there exists an x-y datapair seperated by a space, thusly:
 *      x y
 *
 * PST: FCTVAL = 0 if it gets to the end, displayed output depending on setting 
 *      SHOW_USER_CONTENT and SHOW_USER_OUTPUT
 */
{
        /* Definitions */
        double inx[MAX_PAIRS] = { 0 };          /* input x array */
        double iny[MAX_PAIRS] = { 0 };          /* input y array */
        double x[MAX_PAIRS] = { 0 };            /* x array */
        double y[MAX_PAIRS] = { 0 };            /* y array */
        double shx[MAX_PAIRS] = { 0 };          /* x array after shifting */
        double shy[MAX_PAIRS] = { 0 };          /* y array after shifting */

        int cur_in = 0;                         /* cursor of input arrays */
        int cur_data = 0;                       /* cursor of data arrays */
        double r[MAX_PAIRS] = { 0 };            /* radius, any UOM */
        double theta[MAX_PAIRS] = { 0 };        /* theta, radians */
        ifstream file_in;                       /* input file object */
        ofstream file_out;                      /* output file object */
        bool file_exists = 0;                   /* whether input file exists */

        /* Input */
        file_in.open(FILENAME_IN);
        if (!file_in)
        {
                if (SHOW_USER_CONTENT) {
                        cout << "File \"" << FILENAME_IN << "\" does not"
                                " exist." << endl;
                }
        } else {
                file_exists = 1;
        }
        if (file_exists) {
                /*
                 * The logic tests the following:
                 *  - whether we have space left in our input array
                 *  - whether inputting data returns true (not eof)
                 *  - whether (after input) both of the inputted data values are 
                 *      0 is false (both are zero == false)
                 */
                while (cur_in < MAX_PAIRS
                        && file_in >> inx[cur_in]
                        && file_in >> iny[cur_in]
                        && !(double_equal(inx[cur_in],0,EPSILON)
                        && double_equal(iny[cur_in],0,EPSILON))) {
                        /*
                         * By the way, ^^this^^ stuff is code worth commenting
                         * on because it has some tricky logic, not every time I
                         * declare a variable or run a do/while/if statement,
                         * and not every time I assign an expression.
                         */
                        if (inx[cur_in] > 0 && iny[cur_in] > 0) {
                                x[cur_data] = inx[cur_in];
                                y[cur_data] = iny[cur_in];
                                cur_data++;
                        } else {
                                if (SHOW_USER_CONTENT) {
                                        cout << "Read point (" << inx[cur_in] << 
                                                ", " << iny[cur_in] << "),"
                                                " which is not in Quadrant"
                                                " I...ignoring." << endl;
                                }
                        }
                        if ((cur_in + 1) % 10 == 0 && SHOW_USER_CONTENT) {
                                cout << "Successfully read " << cur_in + 1 <<
                                        " lines of input so far." << endl;
                        }
                        cur_in++;
                }
        }
        file_in.close();

        /* Process */
        if (file_exists) {
                for (int i = 0; i < cur_data; i++) {
                        shx[i] = x[i] + SHIFT_HORIZ;
                        shy[i] = y[i] + SHIFT_VERT;
                        rect_to_polar(shx[i], shy[i], r[i], theta[i]);
                }
        }

        /* Output */
        if (file_exists) {
                file_out.open(FILENAME_OUT);
                for (int i = 0; i < cur_data; i++) {
                        file_out << r[i] << " " << theta[i]*180.0/M_PI << endl;
                }
                if (SHOW_USER_CONTENT) {
                        cout << endl << "Data has been output to file " << 
                                FILENAME_OUT << "," << endl << "where each line"
                                " contains r, then theta, with a space between." 
                                << endl;
                }
                file_out.close();
                if (SHOW_USER_CONTENT && SHOW_USER_OUTPUT) {
                        cout << endl << "Coordinates [inputs ---> polar]:" << 
                                endl << "================================" << 
                                endl;
                        for (int i = 0; i < cur_data; i++) {
                                cout << "(" << x[i] << ", " << y[i] << ")"
                                " ---> (" << r[i] << ", " << theta[i]*180.0/M_PI
                                << ")" << endl;
                        }
                }
        }

        return 0;
}
