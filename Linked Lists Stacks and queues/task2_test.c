#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"

int main(int argc, char **argv)
{
	Stack *stack;
	Queue *queue;
	char **entry, *s;
	int i, num_entries;

	/* parse command line */
	if(argc < 2) {
		fprintf(stderr, "usage: %s ENTRY [ENTRY ...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	num_entries = argc - 1;

	/* allocate memory for entries */
	if(!(entry = (char **) calloc(num_entries, sizeof(char *)))) {
		fprintf(stderr, "error: unable to allocate memory for entries.\n");
		exit(EXIT_FAILURE);
	}
	/* copy entries */
	for(i = 0; i < num_entries; i++) {
		if(!(entry[i] = (char *) calloc(strlen(argv[i + 1]) + 1, sizeof(char)))) {
			fprintf(stderr, "error: unable to allocate memory for entry.\n");
			exit(EXIT_FAILURE);
		}
		memcpy(entry[i], argv[i + 1], sizeof(char) * (strlen(argv[i + 1]) + 1));
	}

	/* TEST 1 - check function error handling */
	/* should print some error messages but program should continue running */
	printf("Performing Test 1...\n");
	push_stack(NULL, NULL, 0);
	push_queue(NULL, NULL, 0);
	pop_stack(NULL);
	pop_queue(NULL);
	peek_stack(NULL);
	peek_queue(NULL);
	print_stack(NULL, print_char);
	print_stack(NULL, NULL);
	print_queue(NULL, print_char);
	print_queue(NULL, NULL);
	free_stack(NULL);
	free_queue(NULL);
	printf("Completed Test 1.\n");

	/* TEST 2 - add and remove all entries from queue and stack */
	printf("Performing Test 2...\n");
	/* initialise queue and stack */
	stack = initialise_stack();
	queue = initialise_queue();

	/* push all entries on to queue and stack */
	for(i = 0; i < num_entries; i++) {
		push_stack(stack, (void *) entry[i], \
			sizeof(char) * (strlen(entry[i]) + 1));
		push_queue(queue, (void *) entry[i], \
			sizeof(char) * (strlen(entry[i]) + 1));
	}

	/* remove all entries from queue and stack */
	for(i = 0; i < num_entries; i++) {
		s = (char *) pop_stack(stack);
		free(s);
		s = (char *) pop_queue(queue);
		free(s);
	}

	/* free memory for queue and stack */
	free_stack(stack);
	free_queue(queue);
	printf("Completed Test 2.\n");

	/* TEST 3 - manipulate entries in queue and stack */
	printf("Performing Test 3...\n");
	/* initialise queue and stack */
	stack = initialise_stack();
	queue = initialise_queue();

	/* push all entries three times on to queue and stack */
	for(i = 0; i < num_entries; i++) {
		push_stack(stack, (void *) entry[i], \
			sizeof(char) * (strlen(entry[i]) + 1));
		push_stack(stack, (void *) entry[i], \
			sizeof(char) * (strlen(entry[i]) + 1));
		push_stack(stack, (void *) entry[i], \
			sizeof(char) * (strlen(entry[i]) + 1));
		push_queue(queue, (void *) entry[i], \
			sizeof(char) * (strlen(entry[i]) + 1));
		push_queue(queue, (void *) entry[i], \
			sizeof(char) * (strlen(entry[i]) + 1));
		push_queue(queue, (void *) entry[i], \
			sizeof(char) * (strlen(entry[i]) + 1));
	}

	/* remove head and tail a few times */
	for(i = 0; i < num_entries; i++) {
		s = (char *) pop_stack(stack);
		free(s);
		s = (char *) pop_stack(stack);
		free(s);
		s = (char *) pop_queue(queue);
		free(s);
		s = (char *) pop_queue(queue);
		free(s);
	}

	/* free memory for entries */
	for(i = 0; i < num_entries; i++)
		free(entry[i]);
	free(entry);

	/* print queue and stack */
	print_stack(stack, print_string);
	print_queue(queue, print_string);

	/* free memory for queue and stack */
	free_stack(stack);
	free_queue(queue);
	printf("Completed Test 3.\n");

	return 0;
}
