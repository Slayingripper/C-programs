CC=gcc
CFLAGS=-Wall -ansi -pedantic-errors
CLIBS=

TEST_ENTRIES_1=this is a fairly short test string.

all: task1_test task2_test

# task 1

linked_list.o: linked_list.c linked_list.h
	$(CC) -c $< $(CFLAGS)

task1_test: task1_test.c linked_list.o
	$(CC) -o task1_test $^ $(CFLAGS) $(CLIBS)

task1_test_run: task1_test
	./task1_test $(TEST_ENTRIES_1)

task1_test_memcheck: task1_test
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./task1_test $(TEST_ENTRIES_1)

# task 2

stack.o: stack.c stack.h
	$(CC) -c $< $(CFLAGS)

queue.o: queue.c queue.h
	$(CC) -c $< $(CFLAGS)

task2_test: task2_test.c stack.o queue.o linked_list.o
	$(CC) -o task2_test $^ $(CFLAGS) $(CLIBS)

task2_test_run: task2_test
	./task2_test $(TEST_ENTRIES_1)

task2_test_memcheck: task2_test
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./task2_test $(TEST_ENTRIES_1)

clean:
	rm -f task1_test task2_test *.o
