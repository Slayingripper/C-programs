#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

/* a node in the linked list */
typedef struct Node
{
	void *data;
	struct Node *next;
	struct Node *prev;
} Node;

/* a linked list */
typedef struct LinkedList
{
	Node *head;
	Node *tail;
} LinkedList;

/* function declarations */
Node *initialise_node(void);
void free_node(Node *);
LinkedList *initialise_linked_list(void);
void free_linked_list(LinkedList *);
Node *append_linked_list(LinkedList *, void *);
Node *prepend_linked_list(LinkedList *, void *);
void remove_head_linked_list(LinkedList *);
void remove_tail_linked_list(LinkedList *);
void print_linked_list(LinkedList *, void (*)(void *));
void print_char(void *);
void print_int(void *);
void print_double(void *);
void print_string(void *);

#endif
