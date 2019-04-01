#ifndef _STACK_H
#define _STACK_H

#include "linked_list.h"

#include <stdlib.h>

typedef LinkedList Stack;

Stack *initialise_stack(void);
void *pop_stack(Stack *);
void push_stack(Stack *, void *, size_t);
void *peek_stack(Stack *);
void print_stack(Stack *, void (*)(void *));
void free_stack(Stack *);

#endif
