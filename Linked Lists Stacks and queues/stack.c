#include "stack.h"
#include "linked_list.h"
#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
/* create a new stack */
/* returns a pointer to the newly created stack */
/* print an error message and return NULL if an error occurs */
Stack *initialise_stack(void)
{
    Stack *stack;
    stack = (Stack*) malloc(sizeof(Stack));
    
    if (stack==NULL){
        fprintf(stderr, "error");
        return NULL;
    }
    
    
    stack->head=NULL;
    stack->tail=NULL;
    return stack;
}
/* free memory for stack *stack */
/* frees memory for all entries in stack and stack itself */
/* print an error message and return if queue is NULL */
void free_stack(Stack *stack)
{
    Node* node;
    Node* nodecancel;
    if (stack==NULL) {
        /*printf("error in linked list function\n");*/
        return;
    }
    node = stack->head;
    while ( node!=NULL) {
        nodecancel=node->prev;
        /* free(node); */
        free(node->data);
        free(node);
        node = nodecancel;
    
   }
   free(stack);
   return;
}

/* remove entry from stack *stack */
/* return data stored in entry */
/* user responsible for freeing returned data */
/* print an error message and return if stack is NULL or empty */
void *pop_stack(Stack *stack)
{
     Node *node;
    void *stacky;

    if(stack==NULL){
       /*printf("Error on remove head\n");*/
        return NULL;
    }
    if ( stack->head == NULL ) 
    {
        /* printf("Error on remove head\n"); */
        return NULL;
    }
    if (stack->head->next == NULL){
        stacky=node->data;        
        node = stack->head;
        stack->head = NULL;
        stack->tail = NULL;
        free_node(node);

        return stacky;
    }

    node = stack->head;
    stacky=node->data;    
    stack->head = stack->head->next;
    stack->head->prev = NULL;
    free(node);

    return stacky;
}    
/* add entry to end of stack *stack */
/* allocate storage of data_size bytes in new entry */
/* copy data referenced by *data to entry */
/* return pointer to newly created entry */
/* print an error message and return if stack is NULL or empty */
/* or if data is NULL */
Node *push_stack(Stack *stack, void *data, size_t data_size)
{
    {
    
    Node *node ;
    if (stack == NULL) {
        /*printf("error on create add node\n");*/
    return NULL;
}


/* node=initialise_node(); */
/* void *stacky; */
/* node->data = (void *)malloc(data_size);
memcpy(node->data, data, data_size); */

/* node->data=data; */
if (stack->tail == NULL) {
    
/*     node->data = data;
 */  
  /* node->next=NULL;
    node->prev=NULL;
    stack->head=node;
    stack->tail=node; */
    return node ;
    
    
        }else{
   /*  node->data = data;   */  
    node->prev = stack->head;
    stack->head->next=node;
    stack->head = node;
    

    return node ;
    }
  
   }

}
/* return pointer to data at start of stack *stack */
/* print an error message and return if stack is NULL or empty */
void *peek_stack(Stack *stack)
{
    

    if(stack==NULL){

        return NULL;
    }
 
 
 
 return stack->head->data;
}
/* print data stored in stack *stack to stdout */
/* prints data from stack top to bottom */
/* prints each entry data on a newline */
/* user gives pointer to function *print_func which is called to print data */
/* print an error message and return if stack or print function is NULL */
/* don't print anything if the stack is empty */
void print_stack(Stack *stack, void (*print_func)(void *))
{
    Node *node;

    if(stack==NULL || print_func==NULL){
        /*printf("error on print linked stack\n");*/
        return;
    }
    node=stack->head;
    while(node!=NULL)
    {
        print_func(node->data);
        node=node->next;
    }
   
    return;
}
