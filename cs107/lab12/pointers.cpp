/*
 * Programmer:  Gregory N. Schmit
 * Section:     4
 * Date:        20160406
 * Program:     Pointers program
 * Description: Class exercise for pointers
 */

#include <iostream>
#include <iomanip>
using namespace std;

void TestPrint(double &a)
{
        double x;
        cout << "local x addr: " << &x << endl << "parameter addr: " << &a
             << endl;
}

int main()
{
        /* Exercise 1 */
        double x;
        double y;
        double *ptr1;
        double *ptr2;

        cout << "STEP 1:" << endl;
        cout << left << setw(20) << "x's value: " << x << endl
             << setw(20) << "x's address: " << &x << endl
             << setw(20) << "y's value: " << y << endl
             << setw(20) << "y's address: " << &y << endl
             << setw(20) << "ptr1's pointee: " << *ptr1 << endl
             << setw(20) << "ptr1 holds address: " << ptr1 << endl
             << setw(20) << "ptr2's pointee: " << *ptr2 << endl
             << setw(20) << "ptr2 holds address: " << ptr2 << endl << endl;

        /* Exercise 2 */
        ptr1 = &x;
        *ptr1 = 1.25;

        cout << "STEP 2:" << endl;
        cout << left << setw(20) << "x's value: " << x << endl
             << setw(20) << "x's address: " << &x << endl
             << setw(20) << "y's value: " << y << endl
             << setw(20) << "y's address: " << &y << endl
             << setw(20) << "ptr1's pointee: " << *ptr1 << endl
             << setw(20) << "ptr1 holds address: " << ptr1 << endl
             << setw(20) << "ptr2's pointee: " << *ptr2 << endl
             << setw(20) << "ptr2 holds address: " << ptr2 << endl << endl;

        /* Exercise 3 */
        y = 2.5;
        ptr1 = &y;

        cout << "STEP 3:" << endl;
        cout << left << setw(20) << "x's value: " << x << endl
             << setw(20) << "x's address: " << &x << endl
             << setw(20) << "y's value: " << y << endl
             << setw(20) << "y's address: " << &y << endl
             << setw(20) << "ptr1's pointee: " << *ptr1 << endl
             << setw(20) << "ptr1 holds address: " << ptr1 << endl
             << setw(20) << "ptr2's pointee: " << *ptr2 << endl
             << setw(20) << "ptr2 holds address: " << ptr2 << endl << endl;

        /* Exercise 4 */
        ptr2 = new double;
        *ptr2 = 10;

        cout << "STEP 4:" << endl;
        cout << left << setw(20) << "x's value: " << x << endl
             << setw(20) << "x's address: " << &x << endl
             << setw(20) << "y's value: " << y << endl
             << setw(20) << "y's address: " << &y << endl
             << setw(20) << "ptr1's pointee: " << *ptr1 << endl
             << setw(20) << "ptr1 holds address: " << ptr1 << endl
             << setw(20) << "ptr2's pointee: " << *ptr2 << endl
             << setw(20) << "ptr2 holds address: " << ptr2 << endl << endl;

        /* Exercise 5 */
        ptr2 = new double;
        *ptr2 = 2*(*ptr1);

        cout << "STEP 5:" << endl;
        cout << left << setw(20) << "x's value: " << x << endl
             << setw(20) << "x's address: " << &x << endl
             << setw(20) << "y's value: " << y << endl
             << setw(20) << "y's address: " << &y << endl
             << setw(20) << "ptr1's pointee: " << *ptr1 << endl
             << setw(20) << "ptr1 holds address: " << ptr1 << endl
             << setw(20) << "ptr2's pointee: " << *ptr2 << endl
             << setw(20) << "ptr2 holds address: " << ptr2 << endl << endl;

        /* Part II */
        int a[10];
        cout << "cout << a: " << a << endl;

        for (int i = 0; i < 10; i++) {
                a[i] = i;
        }

        cout << *(a + 1) << endl << *(a + 7) << endl;

        for (int i = 0; i < 10; i++) {
                cout << (a + i) << endl;
        }

        cout << "x addr: " << &x << endl << "y addr: " << &y << endl;
        TestPrint(x);

        return 0;
}
