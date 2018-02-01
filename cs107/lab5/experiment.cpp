// Programmer:   Gregory N. Schmit
// Section:      4
// Program:      Experiment for radmon number generator
// Date:         20160110
// Description:  Test trials of random number generator

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

bool randommoreodd(int s);

int main()
{
        // Definitions
        int trials = 10000;        //number of trials
        int oddgreater = 0;        //number of trials with more odd
        int evengreater = 0;       //number of trials with more even
        float percentodd = 0.0;    //percentage time that we get more odd
        bool odd = false;          //if trial returns odd
        int s = 0;

        // Process
        for (int i = 0; i < trials; i++)
        {
                odd = randommoreodd(s);
                if (odd == false) {evengreater++;}
                else {oddgreater++;}
                s++;
        }
        percentodd = (static_cast<float>(oddgreater) / 
                static_cast<float>(trials)) * 100.00;
        cout << endl << "Trials with more odd than even: " << oddgreater << endl 
                << "Trials with more even than odd: " << evengreater << endl
                << "Percentage of more odd than even: " << percentodd << endl
                << "Total trials: " << trials << endl;
}

bool randommoreodd(int s)
{
        // Definitions
        const int range = 1001;    //range of random numbers (0 to range)
        const int n = 500;         //number of even randoms to gen, must be > 0
        int r = 0;                 //random number
        int max = 0;               //max random number
        int odd = 0;               //odd integers generated
        int even = 0;              //even integers generated

        // Process
        srand(time(0) + s);
        r = rand() % (range + 1);
        max = r;
        if (r % 2 == 0) {even++;}
        else {odd++;}
        //cout << r << " (max so far: " << max << ")" << endl;
        while (even < n)
        {
                r = rand() % (range + 1);
                if (r > max) {max = r;}
                if (r % 2 == 0) {even++;}
                else {odd++;}
                //cout << r << " (max so far: " << max << ")" << endl;
        }
      //cout << "Generated " << odd << " odd integers while generating " << even
      //        << " even integers, with an overall maximum of " << max << endl;

        if (odd > even) {return true;}
        else {return false;}
}
