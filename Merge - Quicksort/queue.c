#include "queue.h"

#include <stdio.h>
#include <string.h>

Queue *initialise_queue(void)
{
	return initialise_linked_list();
}

void *pop_queue(Queue *queue)
{
	void *data;

	if(!queue->head)
		return NULL;
	data = queue->head->data;
	remove_head_linked_list(queue);

	return data;
}

void push_queue(Queue *queue, void *data, size_t data_size)
{
	append_linked_list(queue, NULL);
	if(!(queue->tail->data = malloc(data_size))) {
		fprintf(stderr, "error: unable to allocate memory for queue data.\n");
		exit(EXIT_FAILURE);
	}
	memcpy(queue->tail->data, data, data_size);
}

void *peek_queue(Queue *queue)
{
	if(!queue->head)
		return NULL;

	return queue->head->data;
}

void print_queue(Queue *queue, void (*print_func)(void *))
{
	print_linked_list(queue, print_func);
}

void free_queue(Queue *queue)
{
	void *data;

	while((data = pop_queue(queue)))
		free(data);
	free_linked_list(queue);
}
