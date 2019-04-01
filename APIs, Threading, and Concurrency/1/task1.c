#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#define LIMIT 100

int main(int argc, char const *argv[])
{
    /* initialise head and tail to NULL */
    struct element *head, *tail = NULL;
    /* create empty list of size equal to LIMIT constant */
    int myList[LIMIT];
    int i;
    /* append numbers from 0 up to LIMIT to myList */
    for(i=0; i<LIMIT; i++)
        myList[i] = i;

    /* add numbers in myList to linked list using addLast, FIFO procedure*/
    for(i=0; i<LIMIT; i++)
        addLast(&myList[i], &head, &tail);
    printf("FIFO\n");
    for(i=1; i<=LIMIT; i++)
    {
        printf("Element %d = %d\n", i, *(int *)removeFirst(&head, &tail));
    }

    /* add numbers in myList to linked list using addFirst, LIFO procedure */
    for(i=0; i<LIMIT; i++)
        addFirst(&myList[i], &head, &tail);
    printf("LIFO\n");
    for(i=1; i<=LIMIT; i++)
    {
        printf("Element %d = %d\n", i, *(int *)removeFirst(&head, &tail));
    }
    return 0;
}
