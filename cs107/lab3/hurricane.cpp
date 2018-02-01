// Programmer:   Gregory N. Schmit
// Section:      4
// Program:      Hurricane
// Date:         20160127
// Description:  Determines hurricane scale (saffir-simpson)

#include <iostream>
#include <string>
using namespace std;

int main()
{
        // Definitions
        float fMaxWindSpeedMPH = -1;  // Max observed wind speed
        string sClassification = "s"; // Classification

        // Input
        cout << "This program will determine what classification (on a Saffir-"
                "Simpson scale) a hurricane is from the maximum observed wind"
                " speed in Miles per Hour (MPH)" << endl << "Enter maximum"
                " observed wind speed in MPH: ";
        cin >> fMaxWindSpeedMPH;
        cout << endl << "You entered: " << fMaxWindSpeedMPH << endl;

        // Process
        if(fMaxWindSpeedMPH >= 0 && fMaxWindSpeedMPH < 39)
        {
                sClassification = "Tropical Despression";
        }
        else if(fMaxWindSpeedMPH >= 39 && fMaxWindSpeedMPH < 74)
        {
                sClassification = "Tropical Storm";
        }
        else if(fMaxWindSpeedMPH >= 74 && fMaxWindSpeedMPH < 96)
        {
                sClassification = "Category 1 Hurricane";
        }
        else if(fMaxWindSpeedMPH >= 96 && fMaxWindSpeedMPH < 111)
        {
                sClassification = "Category 2 Hurricane";
        }
        else if(fMaxWindSpeedMPH >= 111 && fMaxWindSpeedMPH < 130)
        {
                sClassification = "Category 3 Hurricane";
        }
        else if(fMaxWindSpeedMPH >= 130 && fMaxWindSpeedMPH < 157)
        {
                sClassification = "Category 4 Hurricane";
        }
        else if(fMaxWindSpeedMPH >= 157 && fMaxWindSpeedMPH < 800)
        {
                sClassification = "Category 5 Hurricane";
        }
        else if(fMaxWindSpeedMPH >= 800)
        {
                sClassification = "You appear to be on Neptune, with those winds. Try again.";
        }
        else
        {
                sClassification = "You entered inproper input. Try again.";
        }

        // Output
        cout << endl << sClassification << endl;
        
        return 0;
}
