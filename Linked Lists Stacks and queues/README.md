# G51PGA 2017 Coursework 3

## Introduction

This coursework focuses on implementing linked list, stack and queue data structures. There are two tasks to complete, details of which are given below. You should complete **both** tasks. Links to external pages are provided in the details below which you will need to follow and read to complete each task.

## Overview

Unlike previous courseworks where you implemented a complete executable program, in this coursework you will implement a number of library functions. For each task, an executable program is provided which will include and use the library functions which you implement. You will not need to add any files to your forked repository for this coursework, as all the required files are present. For each task, you will add function implementations to certain source files in your repository. A `Makefile` is also provided to build and test your library functions. All tasks will be compiled with the gcc `-ansi -pedantic-errors` switches.

## Assessment

This coursework is worth **20%** of your final course grade. The points awarded for each task are as follows:

|            | Compilation | Implementation | Execution | **Total** |
| ---------- | :---------: | :------------: | :-------: | :-------: |
| **Task 1** | 2           | 2              | 4         | **8**     |
| **Task 2** | 2           | 2              | 4         | **8**     |


For each task, you are awarded *two* points if your program compiles correctly: *one* point if it compiles without errors, and a further *one* point if it compiles without errors *and* warnings. If your program follows the implementation instructions given in the task details below, you are awarded *one* point. If your program is implemented so that no memory leaks occur when it is executed, you are awarded *one* point. If your program produces the correct output as described in the task details below, you are awarded *two* points. If your program handles invalid input correctly as described in the task details below, you are awarded *two* points.

The contribution towards your final course grade is calculated as follows:

```maths
	floor(20 * (task1_points_awarded + task2_points_awarded) / 16)
```

Your provisional score for each task can be viewed on GitLab after every push to `projects.cs.nott.ac.uk.`. Your final score will be based on the code in the last commit pushed to `projects.cs.nott.ac.uk.` *before* the coursework deadline. Commits pushed after the coursework deadline will be disregarded. After the coursework deadline, your code will undergo further review and, based on this review, your provisional score may go up or down. This further review will include checks for code plagiarism and for trivial implementations e.g. implementations just containing an empty main function or clearly not written following the task guidelines. Final scores will be published on the G51PGA moodle pages around a week after the coursework deadline.

Your repository contains a file called `.gitlab-ci.yml`. This file is used during the assessment process and *must not* be removed or edited in any way. Any tampering with this file will result in a score of zero for this coursework.

## Task 1

### Overview

Your task is to implement a generic [doubly linked list](https://en.wikipedia.org/wiki/Doubly_linked_list) library.

A test program `task1_test.c` and linked list library header file `linked_list.h` are provided for you. You must *not* remove or edit these two files in any way.

### Details

A [linked list](https://en.wikipedia.org/wiki/Linked_list) is a frequently used data structure in Computer Science, and often forms the basic for more complex data structures. A generic [doubly linked list](https://en.wikipedia.org/wiki/Doubly_linked_list) is able to store data of any type and size in each of it nodes (also called entries). The header file which contains the interface for an implementation of a generic doubly linked list in C is given in the `linked_list.h` file. A skeleton implementation file `linked_list.c` which implements each of the functions declared in `linked_list.h` is also provided. Your task is to complete the implementation of the functions in `linked_list.c`. You should only edit the `linked_list.c` file, and must *not* edit the `linked_list.h` file.  Your linked list implementation should be of an *open* (not circular) linked list.

In `linked_list.h`, two data structures are defined:

```C
typedef struct Node
{
	void *data;
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct LinkedList
{
	Node *head;
	Node *tail;
} LinkedList;
```

The first data structure, `Node`, is used to represent each node of the linked list. It contains pointers to the next and previous nodes in the list, and a pointer to the data stored at the node. Since you are implementing a *generic* (i.e. able to store any data type) linked list, the data associated with a node is referenced by a void pointer. You should assume that the user is responsible for managing the memory associated with the data stored at the node and pointed to by `void *data`. The second data structure, `LinkedList`, keeps track of the head and tail nodes in the linked list.

The remainder of `linked_list.h` gives the declarations of functions commonly used with linked lists. The (incomplete) implementation of each of these functions is given in `linked_list.c`. You will need to edit the `linked_list.c` file and provide the implementation for each of these functions. You are free to implement the internals of each function in any way you want, but you must *not* change the function definitions in the provided `linked_list.c` file i.e. you must *not* change the function names, return types or parameters. All warnings and error messages in your implementation should be printed to `stderr`. Further implementation guidelines are given in the comments in `linked_list.c`.

A `Makefile` is included which you can use to build and test your implementation. To build your implementation, in the top level of your repository type:

```bash
$ make linked_list.o
```

A test program, `task1_test.c`, is provided which will include your implementation and use your implementation to manipulate a linked list. You must *not* edit the file `task1_test.c`. To compile your implementation and the test program, type:

```bash
$ make task1_test
```

To compile your implementation and the test program and then run the test program, type:

```bash
$ make task1_test_run
```

A typical output (your warning messages may differ) from a correctly working implementation is:

```bash
$ make task1_test_run
./task1_test this is a fairly short test string.
Performing Test 1...
warning: unable to remove head from empty linked list.
warning: unable to remove tail from empty linked list.
warning: unable to append node to linked list.
warning: unable to prepend node to linked list.
warning: unable to print linked list.
warning: unable to print linked list.
warning: unable to free node.
warning: unable to free list.
Completed Test 1.
Performing Test 2...
Completed Test 2.
a
a
fairly
fairly
fairly
short
short
Completed Test 3.
```

Your implementation should handle dynamically allocated memory correctly i.e. free all dynamically allocated memory. As discussed in lectures, a good tool for assessing if a program has handled dynamic memory allocation correctly is `valgrind`. To check your implementation using `valgrind` you can type:

```bash
$ make task1_test_memcheck
```

If your program has correctly handled dynamic memory allocation, the last line of output should read:

```
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Task 2

### Overview

In this task you will use your linked list implementation from Task 1 to implement a [queue](https://en.wikipedia.org/wiki/Queue_(abstract_data_type)) and a [stack](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)).

A test program `task2_test.c` and library header files `queue.h` and `stack.h` are provided for you. You must *not* remove or edit these files in any way.

### Details

Queues and stacks are fundamental data structures in Computer Science. They are commonly implemented using a linked list. You will use your implementation of a linked link from Task 1 to implement a generic queue and stack.

The header files which contain the interface for an implementation of a generic queue and stack in C are given in the `queue.h` and `stack.h` files respectively. Skeleton implementation files `queue.c` and `stack.c` which implement each of the functions declared the interface files are also provided. Your task is to complete the implementation of the functions in `queue.c` and `stack.c`. You should only edit the `queue.c` and `stack.c` files, and must *not* edit the `queue.h` and `stack.h` files. You are free to implement the internals of each function in any way you want, but you must *not* change the function definitions in the provided `queue.c` and `stack.c` files i.e. you must *not* change the function names, return types or parameters. All warnings and error messages in your implementation should be printed to `stderr`. Further implementation guidelines are given in the comments in `queue.c` and `stack.c`.

Unlike the linked list in Task 1, your stack and queue implementations should be responsible for allocating memory for data stored at the entries in the queue or stack. When an entry is added to your queue or stack, memory should be allocated for the data provided by the user, and a copy of the data should be stored in this memory. When a node is removed from your queue or stack, a pointer to the allocated memory for the data should be returned, and it is the responsibility of the user to free the memory allocated for the data. When your queue or stack is destroyed by calling the `free_stack()` or `free_queue()` functions, all allocated memory (included memory allocated for node data) should be freed.

A test program, `task2_test.c`, is provided which will include your implementation and use your implementation to manipulate a queue and stack. You must *not* edit the file `task2_test.c`. To compile your implementation and the test program, type:

```bash
$ make task2_test
```

To compile your implementation and the test program and then run the test program, type:

```bash
$ make task2_test_run
```

A typical output (your warning messages may vary) from a correctly working implementation is:

```bash
$ make task2_test_run
./task2_test this is a fairly short test string.
Performing Test 1...
warning: unable to add entry with empty data.
warning: unable to append node to linked list.
warning: unable to add entry.
warning: unable to pop from empty stack.
warning: unable to pop from empty queue.
warning: unable to peek empty stack.
warning: unable to peek empty queue.
warning: unable to print linked list.
warning: unable to print linked list.
warning: unable to print linked list.
warning: unable to print linked list.
warning: unable to free stack.
warning: unable to free queue.
Completed Test 1.
Performing Test 2...
Completed Test 2.
Performing Test 3...
a
is
is
is
this
this
this
short
test
test
test
string.
string.
string.
Completed Test 3.
```

As in Task 1, your implementation should handle dynamically allocated memory correctly i.e. free all dynamically allocated memory. To check your implementation using `valgrind` you can type:

```bash
$ make task2_test_memcheck
