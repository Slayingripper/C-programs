#ifndef _QUEUE_H
#define _QUEUE_H

#include "linked_list.h"

#include <stdlib.h>

/* a queue */
typedef LinkedList Queue;

/* function declarations */
Queue *initialise_queue(void);
void free_queue(Queue *);
void *pop_queue(Queue *);
Node *push_queue(Queue *, void *, size_t);
void *peek_queue(Queue *);
void print_queue(Queue *, void (*)(void *));

#endif
