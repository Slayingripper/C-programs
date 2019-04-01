#include "linked_list.h"
#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"
/* create a new node */
/* returns a pointer to the newly created node */
/* print an error message and return NULL if an error occurs */
Node *initialise_node(void)
{
    Node *node;
    node = (Node*) malloc(sizeof(Node));
    if (node==NULL){
        printf("error");
        return NULL;
    }
    
    /*node->data=NULL;*/
    node->next=NULL;
    node->prev=NULL;
    
    return node;
}
/* free memory for node *node */
/* print an error message and return if node is NULL */
void free_node(Node *node)
{
  if(node==NULL)
  {
      /*printf("free node error\n");*/
      return;
  }
free(node);
}

/* create a new linked list */
/* returns a pointer to the newly created list */
/* print an error message and return NULL if an error occurs */
LinkedList *initialise_linked_list(void)
{
    LinkedList *list;
    list = (LinkedList *) malloc(sizeof(LinkedList));
    if (list==NULL){
        printf("error");
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

/* free memory for linked list *list */
/* frees memory for all nodes in linked list and list itself */
/* print an error message and return if list is NULL */
void free_linked_list(LinkedList *list)
{
    Node* node;
    Node* nodecancel;
    if (list==NULL) {
        /*printf("error in linked list function\n");*/
        return;
    }
    node = list->head;
   while ( node!=NULL) {
   nodecancel=node;
    node=nodecancel->next;
    free(nodecancel);
    
   }
   free(list);
   return;
}

/* create and add node to the tail of linked list *list */
/* and set data stored at node to *data */
/* should return a pointer to the new node */
/* should return NULL if an error occurs */
Node *append_linked_list(LinkedList *list, void *data)
{
    Node *node;
    
    if(list==NULL){
        /*printf("you cant append to an empty list\n");*/
        return NULL;

    }
    node = initialise_node();
    node->data = data;
    if (list->tail == NULL) {
    list->head=node;
    list->tail=node;
    
    
    return node;
    }
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
    node->data = data;
    

return node;
}


/* create and add node to the head of linked list *list */
/* and set data stored at node to *data */
/* should return a pointer to the new node */
/* should return NULL if an error occurs */
Node *prepend_linked_list(LinkedList *list, void *data)
{
    Node *node;
    

   
    if (list == NULL) {
        /*printf("error on create add node\n");*/
    return NULL;
}
node = initialise_node();
node->data=data;
if (list->tail == NULL) {
    
    node->next=NULL;
    node->prev=NULL;
    list->head=node;
    list->tail=node;
    
}else{
    list->head->prev=node;
    node->next=list->head;

    list->head=node;
}
return node;
}

/* remove head from linked list *list */
/* print an error message and return if list is NULL or empty */
void remove_head_linked_list(LinkedList *list)
{
    Node *node;

    if(list==NULL){
       /*printf("Error on remove head\n");*/
        return ;
    }
    if ( list->head == NULL ) 
    {
        printf("Error on remove head\n");
        return;
    }
    if (list->head->next == NULL){
      /* node = list->head;
        list->head = NULL;
        list->tail = NULL;
        free_node(node);*/

        return;
    }
    node = list->head;
    list->head = list->head->next;
    list->head->prev = NULL;
    free_node(node);
    return;
}    

/* remove tail from linked list *list */
/* print an error message and return if list is NULL or empty */
void remove_tail_linked_list(LinkedList *list)
{
    Node *node;
    
    if(list==NULL){
        /*printf("error on remove tail\n");*/
        return ;
    }
    if ( list->tail == NULL ) 
    {
        printf("error on remove tail\n");
        return;
    }
    if (list->tail->prev == NULL){
        /*node = list->tail;
        list->tail = NULL;
        list->head = NULL;
        free_node(node);*/

        return;
    }
    node = list->tail;
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    free_node(node);
    return;
}


/* print data stored in linked list *list to stdout */
/* prints data from head to tail */
/* prints each node data on a newline */
/* user gives pointer to function *print_func which is called to print data */
/* print an error message and return if list or print function is NULL */
/* don't print anything if the list is empty */
void print_linked_list(LinkedList *list, void (*print_func)(void *))
{
    Node *node;

    if(list==NULL || print_func==NULL){
        /*printf("error on print linked list\n");*/
        return;
    }
    node=list->head;
    while(node!=NULL)
    {
        print_func(node->data);
        node=node->next;
    }
    return;
}

/* print char pointed to by *ptr to stdout */
void print_char(void *ptr)
{
    
    fprintf(stdout,"%c\n",*((char*)ptr));
}

/* print int pointed to by *ptr to stdout */
void print_int(void *ptr)
{
    
    fprintf(stdout,"%d\n",*((int*)ptr));
}

/* print double pointed to by *ptr to stdout */
void print_double(void *ptr)
{
    
    fprintf(stdout,"%f\n",*((double*)ptr));
}

/* print a string pointed to by *ptr to stdout */
void print_string(void *ptr)
{
    
    fprintf(stdout,"%s\n",(char*)ptr);
}
