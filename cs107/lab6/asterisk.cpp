// Programmer:      Gregory N. Schmit
// Section:         4
// Program:         Asterisk
// Date:            2/17/2016
// Description:     Prints asterisks in quantities based on random numbers

#include <iostream>
using namespace std;

void PrintAsterisks()
{
        // Definitions
        int randNum = 0;    // storage for random number generated
        int genCount = 0;   // count of generated numbers

        // Process
        do          // want to run process once first to generate random number
        {
                genCount++;
                randNum = rand() % 81;
                //DEV-test    randNum = 6;
                //DEV-test    cout << genCount << "," << randNum << ": ";
                //DEV-test    if(genCount>=3){randNum = 0;}
                for (int i = 0; i < randNum; i++)   //prints qty of *
                {
                        cout << "*";
                }
                cout << endl;
        } while (randNum % 11 != 0 && genCount < 50);
}

int main()
{
        // Definitions


        // Process
        srand(time(0));
        for (int i = 0; i < 100; i++)    //call print asterisks i times
        {
                cout << "Call " << i + 1 << ":" << endl;
                PrintAsterisks();
        }

        return 0;
}
