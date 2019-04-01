#ifndef _STACK_H
#define _STACK_H

#include "linked_list.h"

#include <stdlib.h>

/* a stack */
typedef LinkedList Stack;

/* function declarations */
Stack *initialise_stack(void);
void free_stack(Stack *);
void *pop_stack(Stack *);
Node *push_stack(Stack *, void *, size_t);
void *peek_stack(Stack *);
void print_stack(Stack *, void (*)(void *));

#endif
