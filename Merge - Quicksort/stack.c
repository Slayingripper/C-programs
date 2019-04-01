#include "stack.h"

#include <stdio.h>
#include <string.h>

Stack *initialise_stack(void)
{
	return initialise_linked_list();
}

void *pop_stack(Stack *stack)
{
	void *data;

	if(!stack->tail)
		return NULL;
	data = stack->tail->data;
	remove_tail_linked_list(stack);

	return data;
}

void push_stack(Stack *stack, void *data, size_t data_size)
{
	append_linked_list(stack, NULL);
	if(!(stack->tail->data = malloc(data_size))) {
		fprintf(stderr, "error: unable to allocate memory for stack data.\n");
		exit(EXIT_FAILURE);
	}
	memcpy(stack->tail->data, data, data_size);
}

void *peek_stack(Stack *stack)
{
	if(!stack->tail)
		return NULL;

	return stack->tail->data;
}

void print_stack(Stack *stack, void (*print_func)(void *))
{
	print_linked_list(stack, print_func);
}

void free_stack(Stack *stack)
{
	void *data;

	while((data = pop_stack(stack)))
		free(data);
	free_linked_list(stack);
}
