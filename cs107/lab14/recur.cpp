/*
 * Programmer:  Gregory N. Schmit
 * Section:     4
 * Date:        20160420
 * Program:     Recur Stars
 * Description: Prints stars using recursion
 */

#include <iostream>
using namespace std;

int f(int n)
{
        int num;
        if (n < 1) {
                num = 0;
        } else if (n == 1 || n == 2 || n == 3) {
                num = n;
        } else if (n > 3) {
                if (!(n % 3)) {
                        num = 2*f(1.0*n/3.0);
                } else {
                        num = f(n - 1) + 2;
                }
        }
        return num;
}

void PrintStars(int lines)
{
        if (lines < 1) { lines = 1; }
        for (int i = 1; i <= lines; i++) {
                int k = f(i);
                for (int j = 0; j < k; j++) {
                        cout << "*";
                }
                cout << endl;
        }
}

int main()
{
        int input;
        cout << "How many lines? (at least 1): ";
        cin >> input;
        PrintStars(input);
        return 0;
}
