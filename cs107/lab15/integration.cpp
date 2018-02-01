/*
 * Programmer:  Gregory N. Schmit
 * Section:     4
 * Date:        20160427
 * Program:     Integration
 * Description: Integration methods (leftb)
 */

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const int INTERVALS = 5;

double f(double x)
{
        return 28.0/5.0 + 2.0*sin(4*x) - 1.0/x;
}

double IntervalArea(double leftb, double rightb)
{
        return f(leftb)*(rightb - leftb);
}

double fArea(double leftb, double rightb, int n)
{
        double w;
        double a;
        w = (rightb - leftb)/n;
        a = 0;
        for (int i = 0; i < n; i++) {
                a = a + IntervalArea(leftb + i*w, leftb + (i + 1)*w);
        }
        return a;
}

int main()
{
        double leftb;
        double rightb;
        int n[INTERVALS] = { 5, 10, 50, 60, 100 };

        cout << "Enter left bound: ";
        cin >> leftb;
        cout << "Enter right bound: ";
        cin >> rightb;

        cout << left << "Results of approximation of f(x) on [" << leftb
                << ", " << rightb << "]:" << endl;
        for (int i = 0; i < INTERVALS; i++) {
                cout << "Using " << n[i] << " subintervals:   " <<
                        fArea(leftb, rightb, n[i]) << endl;
        }

        return 0;
}
