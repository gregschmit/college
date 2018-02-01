/*
 * Programmer:  Gregory N. Schmit
 * Section:     4
 * Date:        20160309
 * Program:     Linear File Search
 * Description: Performs a simple linear search within a file
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int simple_find_in_array(double arr[], int len, double searchkey)
{
        int val = -1;
        int cnt = 0;
        while (cnt < len && val == -1)
        {
                if (arr[cnt] == searchkey) { val = cnt; }
                cnt++;
        }
        return val;
}

int find_in_array(double arr[], int len, int start, double searchkey, double
        tolerance)
{
        int val = -1;
        int cnt = start;
        while (cnt < len && val == -1)
        {
                if (arr[cnt] >= searchkey - tolerance &&
                        arr[cnt] <= searchkey + tolerance)
                {
                        val = cnt;
                }
                cnt++;
        }
        return val;
}

int main()
{
        // Definitions
        const string FILENAME = "data.txt";
        const int MAX_DATA = 100;
        double data[MAX_DATA] = { 0.0 };
        int cur = 0;
        ifstream file;
        double searchkey = 0.0;
        double tolerance = 0.0;

        // Input
        file.open(FILENAME);
        if (!file)
        {
                cout << "File not found" << endl;
        }
        else
        {
                while (cur < MAX_DATA && file >> data[cur])
                {
                        cur++;
                }
        }

        for (int i = 0; i < cur; i++)
        {
                cout << endl << data[i];
        }

        cout << endl;
        cout << "Test 2: " << find_in_array(data,cur,0,2,0) << endl;
        cout << "Test 35.3: " << find_in_array(data,cur,0,35.3,0) << endl;
        cout << "Test 38.3: " << find_in_array(data,cur,0,38.3,0) << endl;
        cout << "Test 9000: " << find_in_array(data,cur,0,9000,0) << endl;
        cout << "Test 35: " << find_in_array(data,cur,0,35,0) << endl;

        cout << endl;
        cout << "Enter search key: ";
        cin >> searchkey;
        cout << "Enter tolerance: ";
        cin >> tolerance;

        // Process
        cout << endl << "Matched values: " << endl;
        for (int i = 0; i < cur; i++)
        {
                if (data[i] <= searchkey + tolerance &&
                        data[i] >= searchkey - tolerance)
                {
                        cout << data[i] << endl;
                }
        }

        // Output

        return 0;
}
