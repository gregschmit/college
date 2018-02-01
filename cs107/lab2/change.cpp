// Programmer:    Gregory N. Schmit
// Section:       4
// Program:       change
// Date:          20160120
// Description:   Counts best coin change given for any quantity

#include <iostream>
using namespace std;

int main()
{
        // Variables
        int cents = 0;
        int quarters = 0;
        int dimes = 0;
        int nickels = 0;
        int pennies = 0;

        // Input
        cout << "This is a program that will tell you the best coin change to give"
                " provided an amount of change (in cents)." << endl << endl <<
                "Please enter an integer representing the quantity of change (in"
                " cents): ";
        cin >> cents;
        
        // Process
        quarters = cents / 25;
        cents = cents % 25;
        dimes = cents / 10;
        cents = cents % 10;
        nickels = cents / 5;
        cents = cents % 5;
        pennies = cents;

        // Output
        cout << "The best coin chainge configuration would be:" << endl << quarters
        << " quarter(s)" << endl << dimes << " dime(s)" << endl << nickels <<
        " nickel(s)" << endl << pennies << " pennie(s)" << endl;

        return 0;
}
