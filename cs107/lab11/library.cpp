/*
 * Programmer:  Gregory N. Schmit
 * Section:     4
 * Date:        20160330
 * Program:     Library
 * Description: Keeps a database of library books and properties
 */

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct BookType
{
        string title;           // title of book
        string author;          // author of book
        string ISBN;            // ISBN of book
        int year;               // year of publication of book
        float listprice;        // list price of book
        float saleprice;        // sale price of book
        bool ishardcover;         // if the book is ishardcover
};

int main()
{
        BookType b1;            // first book
        BookType b2;            // second book
        b1.title = "Adventures of Huckleberry Finn";
        b1.author = "Mark Twain";
        b1.ISBN = "0486280616";
        b1.year = 1994;
        b1.listprice = 4.5;
        b1.ishardcover = false;
        b2.title = "The Adventures of Tom Sawyer";
        b2.author = "Mark Twain";
        b2.ISBN = "1402712162";
        b2.year = 2014;
        b2.listprice = 4.4;
        b2.ishardcover = true;

        // Discount paperback book
        if (b1.ishardcover == false){
                b1.saleprice = b1.listprice * 0.9;
        } else {
                b1.saleprice = b1.listprice;
        }
        if (b2.ishardcover == false){
                b2.saleprice = b2.listprice * 0.9;
        } else {
                b2.saleprice = b2.listprice;
        }

        BookType cheaperBook;   // cheaper book

        // Find cheaper book and pass it to the cheaperBook object
        if (b1.saleprice < b2.saleprice) {
                cheaperBook = b1;
        } else {
                cheaperBook = b1;
        }

        // Print some stuff out
        cout << "The cheaper book is called " << cheaperBook.title <<
                " and it is written by " << cheaperBook.author <<
                " and it costs $" << setprecision(3) << cheaperBook.saleprice <<
                endl;

        return 0;
}
