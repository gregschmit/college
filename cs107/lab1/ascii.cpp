// Programmer:    Gregory N. Schmit
// Section:       4
// Program:       ascii
// Date:          20161515
// Description:   ASCII display program

#include <iostream>
using namespace std;

int main()
{
    char inputChar;
    
    cout << "Type a character: ";
    cin >> inputChar;

    cout << inputChar << "'s ASCII code is: " << int(inputChar) << endl;

    return 0;
}
