#include <stdio.h>

#include "rpn.h"

int main(int argc, char **argv)
{
	Queue *rpn_expr;

	if(argc != 2) {
		fprintf(stderr, "usage: %s EXPRESSION\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	rpn_expr = infix_to_postfix(argv[1]);

	if(!rpn_expr) {
		fprintf(stderr, "error: unable to parse expression.\n");
		exit(EXIT_FAILURE);
	}

	print_queue(rpn_expr, print_string);

 	free_queue(rpn_expr);

	exit(EXIT_SUCCESS);
}
