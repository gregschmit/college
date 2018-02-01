/*
 * Programmer:  Gregory N. Schmit
 * Section:     4
 * Date:        20160302
 * Program:     Data Arrays
 * Description: Do some operations with data arrays and standard deviation.
 */

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
        // Definitions
        const int N = 25;
        int data[N];
        int dloc = 0;
        int input = 0;

        int sum = 0;
        double sd = 0.0;
        double sdavg = 0.0;
        double sdinsum = 0.0;
        
        int num12m = 0;
        int smallest;

        // Input
        for (int i = 0; i < N; i++) {data[i]=0;}
        while (input >= 0)
        {
                cout << "Enter a positive integer or -1 to quit: ";
                cin >> input;
                if (input >= 0)
                {
                        data[dloc] = input;
                        dloc++;
                }
        }

        // Process
        for (int i = 0; i < N; i++)
        {
                sum = sum + data[i];
        }

        sdavg = (double)sum/(double)dloc;
        for (int i = 0; i < dloc; i++)
        {
                sdinsum = sdinsum + pow((double)data[i] - sdavg, 2.0);
        }
        sd = pow((sdinsum / ((double)(dloc - 1))), 0.5);

        for (int i = 0; i < dloc; i++)
        {
                if (data[i] % 12 == 0)
                {
                        num12m++;
                }
        }

        smallest = data[0];
        for (int i = 0; i < dloc; i++)
        {
                if (data[i] < smallest)
                {
                        smallest = data[i];
                }
        }

        // Output
        cout << "Sum: " << sum << endl;
        cout << "Standard Deviation: " << sd << endl;
        cout << "Number of exact multiples of 12: " << num12m << endl;
        cout << "Smallest: " << smallest << endl;

        return 0;
}
