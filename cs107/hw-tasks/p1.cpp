/*
 * Programmer:  Gregory N. Schmit
 * Section:     4
 * Date:        20160420
 * Program:     P1
 * Description: Array of structs
 */

#include <iostream>
#include <string>
using namespace std;

struct DateType
{
        int month;
        int day;
        int year;
};

void PrintDate(struct DateType date)
{
        string month;
        switch (date.month)
        {
                case 1:
                        month = "January";
                        break;
                case 2:
                        month = "February";
                        break;
                case 3:
                        month = "March";
                        break;
                case 4:
                        month = "April";
                        break;
                case 5:
                        month = "May";
                        break;
                case 6:
                        month = "June";
                        break;
                case 7:
                        month = "July";
                        break;
                case 8:
                        month = "August";
                        break;
                case 9:
                        month = "September";
                        break;
                case 10:
                        month = "October";
                        break;
                case 11:
                        month = "November";
                        break;
                case 12:
                        month = "December";
                        break;
        }
        cout << month << " " << date.day << ", " << date.year << endl;
}

void PrintDateArr(struct DateType dates[], int size)
{
        for (int i = 0; i < size; i++)
        {
                PrintDate(dates[i]);
        }
}

int main()
{
        struct DateType input_date[2];
        input_date[0].month = 2;
        input_date[0].day = 17;
        input_date[0].year = 1991;
        input_date[1].month = 4;
        input_date[1].day = 20;
        input_date[1].year = 2016;

        PrintDateArr(input_date, 2);

        return 0;
}
