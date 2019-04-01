#include <stdio.h>
#include <math.h>

#include "rpn.h"

int main(int argc, char **argv)
{
	Queue *rpn_expr;
	double res;

	if(argc != 2) {
		fprintf(stderr, "usage: %s EXPRESSION\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	rpn_expr = infix_to_postfix(argv[1]);

	if(!rpn_expr) {
		fprintf(stderr, "error: unable to parse expression.\n");
		exit(EXIT_FAILURE);
	}

	res = evaluate_rpn(rpn_expr);

	if(res == HUGE_VAL) {
		fprintf(stderr, "error: unable to parse expression.\n");
		exit(EXIT_FAILURE);
	}

	printf("%0.8f\n", res);

 	free_queue(rpn_expr);

	exit(EXIT_SUCCESS);
}
