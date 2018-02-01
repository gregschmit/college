#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct node
{
        struct node *prev;
        int data;
        struct node *next;
};

void insert_sorted(struct node **head, int data)
{
        struct node *newnode;
        newnode = malloc(sizeof(*newnode));
        newnode->data = data;
        if (*head == 0) {
                // special case of void list
                newnode->next = 0;
                newnode->prev = 0;
                *head = newnode;
        } else {
                // regular case
                struct node *cur;
                struct node *prev;
                int doneinserting;
                cur = *head;
                prev = 0;
                doneinserting = 0;
                while (cur != 0 && !doneinserting) {
                        if (cur->data >= data) {
                                // insert new behind cur node
                                newnode->next = cur;
                                newnode->prev = prev;
                                if (prev != 0) { prev->next = newnode; }
                                cur->prev = newnode;
                                if (*head == cur) {
                                        *head = newnode;
                                }
                                doneinserting = 1;
                        } else {
                                // go to next
                                prev = cur;
                                cur = cur->next;
                        }
                }
                // special case of went to end without inserting
                if (!doneinserting) {
                        // insert at end
                        newnode->next = 0;
                        newnode->prev = prev;
                        prev->next = newnode;
                        doneinserting = 1;
                }
        }
        return;
}

void print_ls(struct node *head)
{
        if (head != 0) {
                while (head != 0) {
                        printf("%3d", head->data);
                        head = head->next;
                }
        }
        printf("\n");
        return;
}

int main()
{
        int i;
        struct node *head;
        head = 0;
        srand(time(0));
        for (i=0; i<10; i++) {
                insert_sorted(&head, rand() % 51);
                print_ls(head);
        }
        
        // free memory
        struct node *tmp;
        while (head != 0) {
                tmp = head->next;
                free(head);
                head = tmp;
        }
        
        return 0;
}
