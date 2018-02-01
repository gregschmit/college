/*
 * Programmer:  Gregory N. Schmit
 * Section:     4
 * Date:        20160316
 * Program:     Parallel Array Sorter
 * Description: Program that worst parallel arrays via selection sorting.
 */

#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

void arrswap(double arr[], int i1, int i2)
{
/*
 * PRE: input an array of doubles, and index of values to swap
 * PST: change arr by swapping i1 and i2
 */
        double tmp = 0.0;
        tmp = arr[i1];
        arr[i1] = arr[i2];
        arr[i2] = tmp;
        return;
}

int arrmax(double arr[], int len, int start, int stop)
/*
 * PRE: input an array of doubles, length of the array > 0, and start and stop
 *      should be sensible (see logic for definition of sensible)
 * PST: output max value index
 */
{
        int index = start;
        if ((start >= 0 && start < len)
                && (stop < len && stop >= start)
                && (len > 0)) {
                for (int i = start; i <= stop; i++) {
                        if (arr[i] > arr[index]) {
                                index = i;
                        }
                }
        } else {
                index = -1;
        }
        return index;
}

int arrmin(double arr[], int len, int start, int stop)
/*
 * PRE: input an array of doubles, length of the array > 0, and start and stop
 * PST: output min value index
 */
{
        int index = start;
        if ((start >= 0 && start < len)
                && (stop < len && stop >= start)
                && (len > 0)) {
                for (int i = start; i < stop; i++) {
                        if (arr[i] < arr[index]) {
                                index = i;
                        }
                }
        } else {
                index = -1;
        }
        return index;
}

int main ()
{
        // Definitions
        double x[5];            // test data array
        double y[5];            // test data array parallel to x
        int len = 5;
        int bottom = 0;

        x[0] = 33.35;           // initialize test data arrays
        y[0] = 1;
        x[1] = 26;
        y[1] = 3.2;
        x[2] = 20.1;
        y[2] = 2.1;
        x[3] = 28.123;
        y[3] = 4.3;
        x[4] = 12;
        y[4] = 5.4;

        // Input

        // Process
        bottom = len - 1;
        for (int i = 0; i < len; i++) {
                int tmp = arrmax(x, len, 0, bottom);
                if (tmp != bottom) {
                        arrswap(x, tmp, bottom);
                        arrswap(y, tmp, bottom);
                }
                bottom--;
        }

        // Output
        cout.setf(ios::showpoint);
        cout << setw(10) << "x" << setw(11) << "y" << endl;
        cout << setw(10) << "=====" << setw(11) << "=====" << endl;
        for (int i = 0; i < len; i++) {
                cout << setw(10) << setprecision(3) << x[i] << " " << setw(10)
                        << setprecision(2) << y[i] << endl;
        }

        return 0;
}
