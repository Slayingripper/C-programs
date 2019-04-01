#include "queue.h"
#include "linked_list.h"
#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

/* create a new queue */
/* returns a pointer to the newly created queue */
/* print an error message and return NULL if an error occurs */
Queue *initialise_queue(void)
{
    Queue *queue;
    queue = (Queue*) malloc(sizeof(Queue));
    
    if (queue==NULL){
        fprintf(stderr, "error");
        return NULL;
    }
    
   
    queue->head=NULL;
    queue->tail=NULL;
    return queue;
}

/* free memory for queue *queue */
/* frees memory for all entries in queue and queue itself */
/* print an error message and return if queue is NULL */
void free_queue(Queue *queue)
{
    Node* node;
    Node* nodecancel;
    if (queue==NULL) {
        /*printf("error in linked list function\n");*/
        return;
    }
    node = queue->tail;
   while ( node!=NULL) {
    nodecancel=node->prev;
    /* free(node); */
    free(node->data);
    free(node);
    node = nodecancel;

     
    
   }
   free(queue);
   return;
}

/* remove entry from queue *queue */
/* return data stored in entry */
/* user responsible for freeing returned data */
/* print an error message and return if queue is NULL or empty */
void *pop_queue(Queue *queue)
{
    Node *node;
    void *queuey;

    if(queue==NULL){
       /*printf("Error on remove head\n");*/
        return NULL;
    }
    if ( queue->head == NULL ) 
    {
        /* printf("Error on remove head\n"); */
        return NULL;
    }
    if (queue->head->next == NULL){
        node = queue->head;
        queuey=node->data;                
        queue->head = NULL;
        queue->tail = NULL;
        free_node(node);

        return queuey;
    }
    node = queue->head;
    queuey=node->data;
    
    queue->head = queue->head->next;
    queue->head->prev = NULL;
    free(node);
    
    return queuey;
}    


/* add entry to end of queue *queue */
/* allocate storage of data_size bytes in new entry */
/* copy data referenced by *data to entry */
/* allow data to be NULL */
/* return pointer to newly created entry */
/* print an error message and return if queue is NULL or empty */
Node *push_queue(Queue *queue, void *data, size_t data_size)

{
    Node *node;
    /* void *queuey; */

    if (queue == NULL) {
        /*printf("error on create add node\n");*/
    return NULL;
}

/* node = initialise_node(); */
/* node->data = (void *)malloc(data_size);
memcpy(node->data, data, data_size); */
/* node->data=data; */
if (queue->tail == NULL) {
    
   /*  node->data = data; */
   /*  node->next=NULL;
    node->prev=NULL;
    queue->head=node;
    queue->tail=node; */
    return node ;
    
    
        }else{
   
    queue->tail->next=node;    
    node->prev = queue->tail;
    
    queue->tail = node;
    

    return node ;
    }
}

/* return pointer to data at start of queue *queue */
/* print an error message and return if queue is NULL or empty */
void *peek_queue(Queue *queue)
{
   

    if(queue==NULL){

        return 0;
    }

 return queue->head->data;
}

/* print data stored in queue *queue to stdout */
/* prints data from queue top to bottom */
/* prints each entry data on a newline */
/* user gives pointer to function *print_func which is called to print data */
/* print an error message and return if queue or print function is NULL */
/* don't print anything if the queue is empty */
void print_queue(Queue *queue, void (*print_func)(void *))
{
    Node *node;

    if(queue==NULL || print_func==NULL){
        /*printf("error on print linked queue\n");*/
        return;
    }
    node=queue->head;
    while(node!=NULL)
    {
        print_func(node->data);
        node=node->next;
    }
    return;
}
