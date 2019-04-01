CC=gcc
CFLAGS=-Wall -ansi -pedantic-errors
CLIBS=-lm

TASK1_2_TEST=harmonious pencil push naive jittery greedy billowy practise lock star appear record precede pen lace

TASK3_4_TESTS="5+2-3*4/2^((1.43+2.57)/3)" "4 * (3.332 + 5.668) / 3 ^ 2.0" "-5 + 6 / (+2.76 + 1.24 + +1 ^ 2) - -10.2" "((1+7)-(1*6)" "a+b"

all: task1_test task2_test task3_test task4_test

# libraries

linked_list.o: linked_list.c linked_list.h
	$(CC) -c $< $(CFLAGS)

stack.o: stack.c stack.h
	$(CC) -c $< $(CFLAGS)

queue.o: queue.c queue.h
	$(CC) -c $< $(CFLAGS)

rpn.o: rpn.c rpn.h
	$(CC) -c $< $(CFLAGS)

sort.o: sort.c sort.h
	$(CC) -c $< $(CFLAGS)

# task 1

task1_test: task1_test.c linked_list.o sort.o
	$(CC) -o task1_test $^ $(CFLAGS) $(CLIBS)

task1_test_run: task1_test
	./task1_test $(TASK1_2_TEST)

task1_test_memcheck: task1_test
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./task1_test $(TASK1_2_TEST)

# task 2

task2_test: task2_test.c linked_list.o sort.o
	$(CC) -o task2_test $^ $(CFLAGS) $(CLIBS)

task2_test_run: task2_test
	./task2_test $(TASK1_2_TEST)

task2_test_memcheck: task2_test
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./task2_test $(TASK1_2_TEST)

# task 3

task3_test: task3_test.c stack.o queue.o rpn.o linked_list.o
	$(CC) -o task3_test $^ $(CFLAGS) $(CLIBS)

task3_tests_run: task3_test
	for t in $(TASK3_4_TESTS); do \
		echo ; \
		echo "*** RUNNING TEST ***"; \
		echo "$$ ./task3_test \"$$t\""; \
		./task3_test "$$t"; \
		echo "*** TEST COMPLETE ***"; \
	done

task3_tests_memcheck: task3_test
	for t in $(TASK3_4_TESTS); do \
		echo ; \
		echo "*** RUNNING TEST ***"; \
		echo "$$ valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./task3_test \"$$t\""; \
		valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./task3_test "$$t"; \
		echo "*** TEST COMPLETE ***"; \
	done

# task 4

task4_test: task4_test.c stack.o queue.o rpn.o linked_list.o
	$(CC) -o task4_test $^ $(CFLAGS) $(CLIBS)

task4_test2_memcheck: task4_test
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./task4_test $(TASK3_4_TEST_2)

task4_tests_run: task4_test
	for t in $(TASK3_4_TESTS); do \
		echo ; \
		echo "*** RUNNING TEST ***"; \
		echo "$$ ./task4_test \"$$t\""; \
		./task4_test "$$t"; \
		echo "*** TEST COMPLETE ***"; \
	done

task4_tests_memcheck: task4_test
	for t in $(TASK3_4_TESTS); do \
		echo ; \
		echo "*** RUNNING TEST ***"; \
		echo "$$ valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./task4_test \"$$t\""; \
		valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./task4_test "$$t"; \
		echo "*** TEST COMPLETE ***"; \
	done

clean:
	rm -f task1_test task2_test task3_test task4_test *.o
