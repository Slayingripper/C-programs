#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void addLast(void * oTemp, struct element ** pHead, struct element ** pTail)
{
    /* create an element pointer (node) allocating the same size as the element structure */
    struct element* node = (struct element*)malloc(sizeof(struct element));
    /* assign data and point pNext to null as we are setting node as the tail */
    node->pData = oTemp;
    node->pNext = NULL; 
    /* if pHead or pTail are null then we make node the head of the list */
    if(!(*pHead) || !(*pTail))
        *pHead = node;
    /* if there are elements in the list then make the current tail point to node */
    if(*pTail != NULL)
        (*pTail)->pNext = node;
    /* set pTail to node */
    *pTail = node;
}

void addFirst(void * oTemp, struct element ** pHead, struct element ** pTail)
{   
    /* create an element pointer (node) allocating the same size as the element structure */
    struct element* node = (struct element*)malloc(sizeof(struct element));
    /* assign the data to node */
    node->pData = oTemp;
    node->pNext = NULL; 
    /* if there is no tail make the node the tail */
    if(!*pTail)
        *pTail = node;
    /* if there are any other nodes in the list then point the new node to the current head */
    if(*pHead != NULL) 
        node->pNext = *pHead;
    /* make the new node the head */
    *pHead = node;
}

void * removeFirst(struct element ** pHead, struct element ** pTail)
{
    /* check if the is a head the linked list*/
    if(!pHead)
    {
        fprintf(stderr, "No head in the list\n");
        return NULL;
    }
    void *data = (*pHead)->pData;
    struct element *pNewHead = NULL;
    /* if the head isnt the tail we temporary store new head in pNewHead*/
    if((*pHead)->pNext != NULL)
        pNewHead = (*pHead)->pNext;
    /* Free the current head and set the new head to pNewHead*/
    free(*pHead);
    *pHead = pNewHead;
    /* set tail to null if head is null */
    if(!pHead)
        *pTail = NULL;
    return data;
     
}

