#include <iostream>
#include <string>
using namespace std;

int main()
{
        string a;
        string b;
        string c;
        string d;
        int i;
        i = 28;
        d = to_string(i);
        b = "strb";
        c = "strc";
        a = b + " " + c + to_string(i);
        cout << a << endl;
        return 0;
}
