#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

#define TEST_INT_LEN 10

int main(int argc, char **argv)
{
	LinkedList *list;
	int i;

	/* parse command line */
	if(argc < 2) {
		fprintf(stderr, "usage: %s LIST_ENTRY [LIST_ENTRY ...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* TEST 1 - check function error handling */
	/* should print some error messages but program should continue running */
	printf("Performing Test 1...\n");
	remove_head_linked_list(NULL);
	remove_tail_linked_list(NULL);
	if(append_linked_list(NULL, NULL)) {
		fprintf(stderr, "error: able to append to nonexistant linked list.\n");
		exit(EXIT_FAILURE);
	}
	if(prepend_linked_list(NULL, NULL)) {
		fprintf(stderr, "error: able to prepend to nonexistant linked list.\n");
		exit(EXIT_FAILURE);
	}
	print_linked_list(NULL, print_char);
	print_linked_list(NULL, NULL);
	free_node(NULL);
	free_linked_list(NULL);
	printf("Completed Test 1.\n");

	/* TEST 2 - add and remove all entries from list */
	printf("Performing Test 2...\n");
	/* initialise list */
	list = initialise_linked_list();

	/* add all entries to list */
	for(i = 1; i < argc; i++) {
		append_linked_list(list, (void *) argv[i]);
	}

	/* remove all entries from list */
	for(i = 1; i < argc; i++) {
		remove_head_linked_list(list);
	}

	/* add all entries to list */
	for(i = 1; i < argc; i++) {
		append_linked_list(list, (void *) argv[i]);
	}

	/* remove all entries from list */
	for(i = 1; i < argc; i++) {
		remove_tail_linked_list(list);
	}

	/* free memory for linked list */
	free_linked_list(list);
	printf("Completed Test 2.\n");

	/* TEST 3 - manipulate entries in list */
	printf("Performing Test 3...\n");
	/* initialise list */
	list = initialise_linked_list();

	/* add all entries three times to list */
	for(i = 1; i < argc; i++) {
		append_linked_list(list, (void *) argv[i]);
		append_linked_list(list, (void *) argv[i]);
		append_linked_list(list, (void *) argv[i]);
	}

	/* remove head and tail a few times */
	for(i = 1; i < argc; i++) {
		remove_head_linked_list(list);
		remove_tail_linked_list(list);
	}

	/* print list */
	print_linked_list(list, print_string);

	/* free memory for linked list */
	free_linked_list(list);
	printf("Completed Test 3.\n");

	return 0;
}
