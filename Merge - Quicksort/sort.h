#ifndef _SORT_H
#define _SORT_H

#include "linked_list.h"

void insertion_sort(LinkedList *, int (*)(void *, void *));
void merge_sort(LinkedList *, int (*)(void *, void *));

#endif
