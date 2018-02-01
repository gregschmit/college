/*
 * Programmer:  Gregory N. Schmit
 * Section:     4
 * Date:        20160413
 * Program:     Linked Lists
 * Description: Demo for linked lists.
 */

#include <iostream>
using namespace std;

struct lliNode;

typedef lliNode *lliNodePtr;

struct lliNode
{
        int data;
        lliNodePtr next;
};

void PrintList(lliNodePtr head)
{
        lliNodePtr cur;
        cur = head;
        while (cur != NULL) {
                cout << (*cur).data << endl;
                cur = (*cur).next;
        }
        cout << "Done!" << endl << endl;
}

int main()
{
        lliNodePtr head;
        lliNodePtr tmp;

        // Step 1
        head = new lliNode;
        tmp = new lliNode;
        (*head).data = 5;

        PrintList(head);

        // Step 2
        (*tmp).data = 8;
        (*tmp).next = head;
        head = tmp;

        PrintList(head);

        // Step 3
        tmp = new lliNode;
        (*tmp).data = 12;
        (*(*head).next).next = tmp;

        PrintList(head);

        // Step 4
        tmp = new lliNode;
        (*tmp).data = 7;
        (*tmp).next = (*(*head).next).next;
        (*(*head).next).next = tmp;

        PrintList(head);

        // Step 5
        tmp = (*head).next;
        (*head).next = (*(*head).next).next;
        delete tmp;

        PrintList(head);

        // delete list
        tmp = (*(*(*head).next).next).next;
        delete tmp;
        tmp = (*(*head).next).next;
        delete tmp;
        tmp = (*head).next;
        delete tmp;
        tmp = head;
        delete head;

        return 0;
}
