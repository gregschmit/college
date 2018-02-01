// Programmer:   Gregory N. Schmit
// Section:      4
// Program:      Random number generator
// Date:         20160110
// Description:  Generates random numbers between 0 and 1000

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
        // Definitions
        const int range = 1000;    //range of random numbers (0 to range)
        const int n = 500;         //number of even randoms to gen, must be > 0
        int r = 0;                 //random number
        int max = 0;               //max random number
        int odd = 0;               //odd integers generated
        int even = 0;              //even integers generated

        // Process
        srand(time(0));
        r = rand() % (range + 1);
        max = r;
        if (r % 2 == 0) {even++;}
        else {odd++;}
        cout << r << " (max so far: " << max << ")" << endl;
        while (even < n)
        {
                r = rand() % (range + 1);
                if (r > max) {max = r;}
                if (r % 2 == 0) {even++;}
                else {odd++;}
                cout << r << " (max so far: " << max << ")" << endl;
        }
        cout << "Generated " << odd << " odd integers while generating " << even 
                << " even integers, with an overall maximum of " << max << endl;

        return 0;
}
