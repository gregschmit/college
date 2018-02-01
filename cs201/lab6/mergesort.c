#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct CELL *LIST;
struct CELL {
        char firstname[16];
        char lastname[16];
        LIST next;
        };
// return's 0 if value not in List, returns 1 if value is in List

void printList(LIST ptr){
        printf("the list contains:\n");
        while (ptr != NULL)
        {
                printf("%s %s\n",ptr->firstname, ptr->lastname);
                ptr = ptr->next;
        }
        printf("\n\n");
}

LIST insert (LIST ptr, char firstname[16], char lastname[16]){
        // need to malloc space for new value
        LIST tempnode = (LIST)malloc(sizeof(struct CELL));
        tempnode->next = NULL;
        strcpy(tempnode->firstname, firstname);
        strcpy(tempnode->lastname, lastname);
        
        // splice into list 
        
        tempnode->next = ptr; // this should be first, so we don't lose
        // the rest of the list
        // reassign head
        ptr = tempnode;
        //printf("in Insert ");
        //printList(ptr);
        return(ptr);
        }
        
LIST split (LIST list){
        LIST secondlist;
        if (list == NULL) // is list empty
        {
                return NULL;
        } else { 
                if (list->next == NULL){ // only 1 item in list, keep it with head
                        return NULL;// make second list empty
                } else {
                secondlist = list->next; // created secondlist to point to node with 7 in example
                list->next = secondlist->next; // moves the pointer
                secondlist->next = split(secondlist->next);
                return secondlist;
                }
        }
}

LIST merge(LIST list1, LIST list2)
{
        int i;
        if (list1 == 0) { return list2; }
        if (list2 == 0) { return list1; }
        if (strcmp(list1->firstname, list2->firstname) < 0) {
                list1->next = merge(list1->next,list2);
                return list1;
        } else {
                list2->next = merge(list1,list2->next);
                return list2;
        }
}
        
LIST mergesortclass(LIST head)
{
        LIST secondlist;
        if (head == NULL)
        {
                return NULL;
        }
        else {
                if (head->next == 0) {
                        return head;
                } else {
                        secondlist = split(head);
                        printf("list1: ");
                        printList(head);
                        printf("list2: ");
                        printList(secondlist);

                        head=mergesortclass(head);
                        secondlist=mergesortclass(secondlist);
                        return merge(head,secondlist);
                }
        }
}        
        
int main() {

        LIST head = NULL;
        printList(head);
        head = insert(head, "Jane", "Smith");
        printList(head);
        head = insert(head, "Fred", "Smith");
        printList(head);
        head = insert(head, "Mary", "Smith");
        printList(head);
        head = insert(head, "Jane", "Jones");
        printList(head);
        head = insert(head, "Bill", "Jones");
        printList(head);
        head = insert(head, "Fred", "Doe");
        printList(head);
        head = insert(head, "Jane", "Doe");
        printList(head);
        head = insert(head, "Phil", "Doe");
        printList(head);


        head = mergesortclass(head);
        printList(head);
        return 0;
}
