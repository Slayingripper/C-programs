#ifndef _RPN_H
#define _RPN_H

#include "queue.h"

Queue *infix_to_postfix(char *);
double evaluate_rpn(Queue *);

#endif
