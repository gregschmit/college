/*
* -Skeleton code for Lab 5-
* Fill in the code for insert and delete.
* The main function already provides the interface --
* you just need to fill in the functions. You can
* use any code from class or your previous lab. Feel
* free to change the return values/params as you like.
*/

#include<stdio.h>
#include<stdlib.h>

/*
Our struct for a doubly-linked list node
*/
typedef struct CELL *LIST;
struct CELL {
        int element;
        LIST next;
        LIST prev;
};

/*
Print the current linked list forwards and backwards
*/
void printList(LIST head)
{
        LIST tail=head;
        printf("forwards: ");
        while (head != NULL)
        {
                printf("%d ",head->element);
                head = head->next;
                if (head!= NULL)
                        tail = head;
        }
        printf("\nbackwards:");
        while (tail != NULL)
        {
                printf("%d ",tail->element);
                tail = tail->prev;
        }
        printf("\n");
}

void insertNodeSorted(int newnum, LIST *head)
{
        LIST tmpptr=*head;

LIST newnode = (LIST)malloc(sizeof(struct CELL));
newnode->prev = NULL;
newnode->next = NULL;
newnode->element = newnum;
/* what are the possible cases for inserting this node
1. list is empty, just make head point to newnode
2. insert in the middle of the list 
3. insert before head node
4. insert after the last node
*/
        if ((*head)==NULL)
                *head = newnode;
        else {
                while ((tmpptr->next != NULL) && (tmpptr->element < newnum))
                        tmpptr = tmpptr->next;
                // now insert the node
                if (tmpptr->element >= newnum){
                        newnode->next = tmpptr;
                        newnode->prev = tmpptr->prev;
                        if (tmpptr->prev != NULL)
                                tmpptr->prev->next = newnode;
                        else
                                (*head)=newnode;
                        tmpptr->prev = newnode;
                } else {
                        tmpptr->next = newnode;
                        newnode->prev = tmpptr;
                }
        }
        
}

/*
In the simplest case, if a number doesn't exist 
in the list to delete, nothing happens.
*/
void deleteNode(int num, LIST* head)
{
        if (*head == 0) { return; }     // void list
        LIST tmp = *head;
        int found;
        // find node (increment tmp)
        found = 0;
        while (tmp->next != 0 && !found) {
                if (tmp->element == num) {
                        found = 1;
                } else {
                        tmp = tmp->next;
                }
        }
        if (tmp->element == num) { found = 1; }
        // reorganize next and prev and free tmp
        if (!found) { return; }         // not found
        if (tmp->prev == 0) {
                // node at beginning of list
                tmp->next->prev = 0;
                *head = tmp->next;
                free(tmp);
        } else if (tmp->next == 0) {
                // node at end of list
                printf("\nmuhaha\n");
                tmp->prev->next = 0;
                free(tmp);
        } else {
                // general case
                tmp->next->prev = tmp->prev;
                tmp->prev->next = tmp->next;
                free(tmp);
        }
        return;
}

int main() 
{
        LIST head = NULL;
        int newnum;
        int running = 1, inserting = 1;
        
        /*
        Asks the user for positive numbers and keeps adding them to the list in 
ascending order.
        After each input, the list prints out forwards and backwards.
        -1 means exit the program, 0 means switch (between inserting and 
deleting).
        */
        while (running)
        {
                while (inserting)
                {
                        printf("\nEnter a positive number to add to the list (0"
                                " to delete, -1 to exit): ");
                        scanf("%d", &newnum);
                        if (newnum == 0)
                        {
                                inserting = 0;
                        }
                        else if (newnum == -1)
                        {
                                running = 0;
                                break;
                        }
                        else
                        {
                                insertNodeSorted(newnum, &head);
                                printList(head);
                        }
                }
                
                while (!inserting)
                {
                        printf("\nEnter a positive number to delete from the"
                                " list (0 to insert, -1 to exit): ");
                        scanf("%d", &newnum);
                        if (newnum == 0)
                        {
                                inserting = 1;
                        }
                        else if (newnum == -1)
                        {
                                running = 0;
                                break;
                        }
                        else
                        {
                                deleteNode(newnum, &head);
                                printList(head);
                        }
                }
        }
}
