/*
 * Programmer:  Gregory N. Schmit
 * Section:     4
 * Date:        20160420
 * Program:     P2
 * Description: List insertion at head
 */

#include <iostream>
using namespace std;

struct lliNode
{
        int data;
        struct lliNode *next;
};

void InsertAtIndexStupid(struct lliNode *head, int key, int index)
{
        /* this method is garbage; I need to think better */
        struct lliNode *cur;
        struct lliNode *prev;
        struct lliNode *next;
        int cnt;

        if (!head || index < 0) { return; }

        cur = head;
        prev = 0;
        next = 0;
        cnt = 0;

        do {
                if (cnt == index) {
                        next = new struct lliNode;
                        *next = *cur;
                        cur->data = key;
                        cur->next = next;
                        if (prev) { prev->next = cur; }
                }
                prev = cur;
                cur = cur->next;
                cnt++;
        } while (cur && cnt < index);
        /* Seriously, if I cought someone writing this for a project I would
                remove them from the team for all of our intellectual safety. */
}

void InsertAtIndex(struct lliNode *head, int key, int index)
{
        if (!head || index < 0) { return; }

        struct lliNode *prev;
        struct lliNode *next;
        struct lliNode *insert;
        int cnt;

        prev = 0;
        next = head;
        insert = new struct lliNode;
        insert->data = key;
        cnt = 0;

        while (cnt < index && next->next) {
                prev = next;
                next = next->next;
                cnt++;
        }

        if (prev) {
                insert->next = prev->next;
                prev->next = insert;
        } else {
                insert->next = head;
                head = insert;
        }
}

void InsertAtHead(struct lliNode *head, int key)
{
        struct lliNode *tmp;

        tmp = new struct lliNode;
        tmp->data = head->data;
        tmp->next = head->next;

        head->data = key;
        head->next = tmp;
}

void InsertAtTail(struct lliNode *head, int key)
{
        struct lliNode *cur;
        struct lliNode *tail;

        cur = head;

        tail = new struct lliNode;
        tail->data = key;
        tail->next = 0;

        while (cur->next) {
                cur = cur->next;
        }

        cur->next = tail;
}

void DeleteKey(struct lliNode *head, int key)
{
        struct lliNode *cur;
        struct lliNode *prev;

        
}

void PrintList(struct lliNode *head)
{
        struct lliNode *cur;

        cur = head;

        while (cur) {
                cout << cur->data << endl;
                cur = cur->next;
        }

        cout << endl;
}

void PrintListRecur(struct lliNode *head)
{
        cout << head->data << endl;
        if (head->next) { PrintListRecur(head->next); }
}

void DeleteLL(struct lliNode* head)
{
        struct lliNode *cur;
        struct lliNode *next;

        cur = head;
        next = 0;

        do {
                if (cur) {
                        next = cur->next;
                }
                delete cur;
                cur = next;
        } while (next);
}

int main()
{
        struct lliNode *head;
        struct lliNode *tmp;

        head = new struct lliNode;
        head->data = 1;
        tmp = new struct lliNode;
        tmp->data = 2;
        head->next = tmp;
        tmp = new struct lliNode;
        tmp->data = 3;
        head->next->next = tmp;

        DeleteLL(0);

        PrintListRecur(head);
        cout << endl;

        InsertAtHead(head, 8);

        PrintListRecur(head);
        cout << endl;

        InsertAtTail(head, 200);

        PrintListRecur(head);
        cout << endl;

        InsertAtIndex(head, 0, 450);

        PrintListRecur(head);
        cout << endl;

        InsertAtIndex(head, 3, 203);

        PrintListRecur(head);
        cout << endl;

        InsertAtIndex(head, 20, 220);

        PrintListRecur(head);
        cout << endl;

        InsertAtIndex(head, 9, 209);

        PrintListRecur(head);
        cout << endl;

        DeleteLL(head);

        return 0;
}
