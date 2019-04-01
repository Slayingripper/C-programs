#include "sort.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "stack.h"


/* sort linked list *list using merge insertion sort. */
/* upon success, the elements in *list will be sorted. */
/* return silently if *list is uninitialised or empty. */
/* the compare argument is a pointer to a function which returns */
/* less than 0, 0, or greater than 0 if first argument is */
/* less than, equal to, or greater than second argument respectively. */
void insertion_sort(LinkedList *list, int (*compare)(void *, void *))
{
    Node *B,*C;
   LinkedList *bacon; 
   bacon = initialise_linked_list();
    if(list==NULL)
    {
        return;
    }
    
    prepend_linked_list(bacon,list->head->data);
    remove_head_linked_list(list);
    

    while(list->head !=NULL) {
       
                B=bacon->head;
                        
                while(B!=NULL)
        {   
            
    if((*compare)(list->head->data,B->data)<0)       {
                            if(B==bacon->head)
        {
                   
        prepend_linked_list(bacon,list->head->data);     
          remove_head_linked_list(list);
                   
                break; 
                }
                else
                {
                    
         C=initialise_node();
      C->data=list->head->data;        
               C->prev=B->prev;        
                C->next=B;
                    
      B->prev->next=C;
        B->prev=C;
              remove_head_linked_list(list);
       break; 
                }               
                
               
                
            }    
            
            B=B->next;
        }
        if(B==NULL)
        {   
            
            append_linked_list(bacon,list->head->data);
            remove_head_linked_list(list);
        }
        
    }
    
 *list=*bacon;
  free(bacon);  

}

/* sort linked list *list using merge sort algorithm. */
/* upon success, the elements in *list will be sorted. */
/* return silently if *list is uninitialised or empty. */
/* the compare argument is a pointer to a function which returns */
/* less than 0, 0, or greater than 0 if first argument is */
/* less than, equal to, or greater than second argument respectively. */
void merge(LinkedList *list,LinkedList *lettuce ,LinkedList *tomatoe, int (*compare)(void *, void *));
void merge_sort(LinkedList *list, int (*compare)(void *, void *))
{
    
    LinkedList *lettuce;
    LinkedList *tomatoe;
    if(!list)
    {
                return ;
    }

    if(list->head==NULL || list->head->next==NULL)
    {
        return;
    }
    tomatoe=initialise_linked_list();
    lettuce=initialise_linked_list();
   while(list->head){
    
    append_linked_list(lettuce,list->head->data);
    
    
    remove_head_linked_list(list); 
   
    if(list->head){
        
        append_linked_list(tomatoe,list->head->data);
        

        remove_head_linked_list(list);
        
    }
    
}

merge_sort(lettuce,compare);
merge_sort(tomatoe,compare); 
merge(list,lettuce,tomatoe,compare);




} 
void merge(LinkedList *list,LinkedList *lettuce ,LinkedList *tomatoe, int (*compare)(void *, void *))
{
    while(lettuce->head && tomatoe->head)
{
    if((*compare)(lettuce->head->data,tomatoe->head->data)<0)
{

    append_linked_list(list,lettuce->head->data);
    remove_head_linked_list(lettuce);
}
else
{
    append_linked_list(list,tomatoe->head->data);
    remove_head_linked_list(tomatoe);
}
}
        while(lettuce->head)
{
    append_linked_list(list,lettuce->head->data);
    remove_head_linked_list(lettuce);
}
        while(tomatoe->head)
{
    append_linked_list(list,tomatoe->head->data);
    remove_head_linked_list(tomatoe);
    }
    free(lettuce);
    free(tomatoe);
}
