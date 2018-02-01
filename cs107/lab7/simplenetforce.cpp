// Programmer:  Gregory N. Schmit
// Section:     4
// Date:        20160224
// Program:     Simple Net Force
// Description: Performs simple calculation of net force vectors

#include <iostream>
#include <cmath>
using namespace std;

double FsubX(double m, double a, double theta)   // x-component of F
{
        // PRE:  m is double; > 0; in kg
        //       acceleration is double in m/s^2
        //       theta is a double in radians
        // POST: return y-component of force in newtons
        return m*a*cos(theta);
}

double FsubY(double m, double a, double theta)   // y-component of F
{
        // PRE:  m is double; > 0; in kg
        //       acceleration is double in m/s^2
        //       theta is a double in radians
        // POST: return y-component of force in newtons
        return m*a*sin(theta);
}

void testdriver()
{
        // Definitions
        double mass = 0.0;              // mass in kg
        double acceleration = 0.0;      // acceleration in m/s^2
        double thetadeg = 0.0;          // theta in degrees
        double thetarad = 0.0;          // theta in radians

        // Process
        mass = 1;
        acceleration = 1;
        thetadeg = 45;
        thetarad = thetadeg*M_PI/180.0;
        cout << "test: m=1, a=1, theta=45, should get <.707, .707>" << endl <<
                "FsubX: " << FsubX(mass, acceleration, thetarad) << endl << 
                "FsubY: " << FsubY(mass, acceleration, thetarad) << endl << 
                endl;
        cout << "test: m=10, a=10, theta=45, should get <70.7, 70.7>" << endl 
                << "FsubX: " << FsubX(10,10,M_PI/4.0) << endl << "FsubY: " << 
                FsubY(10,10,M_PI/4.0) << endl << endl;
        cout << "test: m=2, a=5, theta=90, should get <0, 10>" << endl <<
                "FsubX: " << FsubX(2,5,M_PI/2) << endl << "FsubY: " << 
                FsubY(2,5,M_PI/2) << endl << endl;
        cout << "test: m=5, a=-2, theta=0, should get <-10, 0>" << endl 
                << "FsubX: " << FsubX(5,-2,0) << endl << "FsubY: " << 
                FsubY(5,-2,0) << endl << endl;
}

int main()
{
        // PRE:  mass is double; > 0; in kg
        //       acceleration is a double in m/s^2
        //       theta is a double in degrees
        // POST: display horiz and vert components of force in newtons; convert 
        //       theta to radians before passing to functions because they are 
        //       for adults

        // Definitions
        double mass = 0.0;              // mass in kg
        double acceleration = 0.0;      // acceleration in m/s^2
        double thetadeg = 0.0;          // theta in degrees
        double thetarad = 0.0;          // theta in radians

        testdriver();
        cout << endl;

        // Input
        cout << "This program calculates the x and y components of the force" 
                " vector given mass (kg), acceleration (m/s^2), and theta" 
                " (degrees)" << endl;
        do
        {
                cout << "Input non-negative mass (in kg): ";
                cin >> mass;
        } while(mass < 0);
        cout << "Input accelertion (in m/s^2): ";
        cin >> acceleration;
        cout << "Input angle above horizontal (in degrees): ";
        cin >> thetadeg;

        // Process
        thetarad = thetadeg*M_PI/360.0;
        cout << "F, x-component: " << FsubX(mass, acceleration, thetarad) << 
                endl << "F, y-component: " << FsubY(mass, acceleration, 
                thetarad) << endl;

        return 0;
}
