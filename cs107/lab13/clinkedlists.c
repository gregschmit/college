/*
 * Programmer:  Gregory N. Schmit
 * Section:     4
 * Date:        20160413
 * Program:     C Linked Lists
 * Description: Demo for linked lists - without typedef and using c
 */

#include <stdio.h>
#include <stdlib.h>

struct lliNode
{
        int data;
        struct lliNode* next;
};

void PrintList(struct lliNode* start)
{
        struct lliNode* cur;
        cur = start;
        while (cur) {
                printf("%i\n", (*cur).data);
                cur = (*cur).next;
        }
        printf("Done!\n\n");
}

int main()
{
        struct lliNode* head;
        struct lliNode* tmp;

        // Step 1
        head = malloc(sizeof(*head));
        tmp = malloc(sizeof(*tmp));
        (*head).data = 5;

        PrintList(head);

        // Step 2
        (*tmp).data = 8;
        (*tmp).next = head;
        head = tmp;

        PrintList(head);

        // Step 3
        tmp = malloc(sizeof(*tmp));
        (*tmp).data = 12;
        (*(*head).next).next = tmp;

        PrintList(head);

        // Step 4
        tmp = malloc(sizeof(*tmp));
        (*tmp).data = 7;
        (*tmp).next = (*(*head).next).next;
        (*(*head).next).next = tmp;

        PrintList(head);

        // Step 5
        tmp = (*head).next;
        (*head).next = (*(*head).next).next;
        free(tmp);

        PrintList(head);

        // delete list
        tmp = (*(*(*head).next).next).next;
        free(tmp);
        tmp = (*(*head).next).next;
        free(tmp);
        tmp = (*head).next;
        free(tmp);
        tmp = head;
        free(head);

        return 0;
}
