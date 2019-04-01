#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "linkedlist.h"
#include "coursework.h"

/* Define counters and semaphores */
int items, produced, consumed = 0; 

sem_t delay_consumer;
sem_t delay_producer;
sem_t sync; 

struct element *head = NULL;
struct element *tail = NULL;

/* printProcess will take either "Producer" or "Consumer" as a parameter */
/* it prints the type of process and how many processes have been consumed or produced */
/* finally it will print the number of stars corresponding to processes in the buffer */
void printProcesses(char process[9])
{
    printf("%s, Produced = %d, Consumed = %d: ", process , produced, consumed);
    for(int i = 0; i < items; i++)
        printf("*");
    printf("\n");
    return;
}

/* consumer function will call sem_wait on the delay_consumer semaphore */
/* it iterates through the all of the threads and frees the process at the front of the buffer */
/* its posts the delay_producer semaphore if the buffer is full */
/* it will wait the delay_consumer semaphore if the buffer is empty */
/* exits the thread once all the jobs have been consumed */
void * consumer (void * p)
{
	sem_wait(&delay_consumer);
	for(int i = 0; i < MAX_NUMBER_OF_JOBS; i++)
	{
		sem_wait(&sync);
		items--;
		consumed++;
        free(removeFirst(&head, &tail));
		printProcesses("Consumer\0");
		if(items == MAX_BUFFER_SIZE-1)
			sem_post(&delay_producer);
		sem_post(&sync);
		if (items == 0)
			sem_wait(&delay_consumer);
	}
	sem_post(&delay_producer);
	pthread_exit(0);
}

/* producer function will call sem_wait on the delay_producer semaphore */
/* generates a new process at the end of the buffer for MAX_NUMBER_OF_JOBS processes */
/* its posts the delay_consumer semaphore if the buffer has 1 item in it */
/* it will wait the delay_producer semaphore if the buffer full*/
/* exits the thread once all the jobs have been produced */
void * producer(void * p)
{
	sem_wait(&delay_producer);
	for(int i = 0; i < MAX_NUMBER_OF_JOBS; i++)
	{
		sem_wait(&sync);
        addLast(generateProcess(), &head, &tail);
		items++;
		produced++;
        printProcesses("Producer\0");
		if (items == 1)
			sem_post(&delay_consumer);
		sem_post(&sync);
		if(items == MAX_BUFFER_SIZE)
			sem_wait(&delay_producer);
	}
	sem_post(&delay_consumer);
	pthread_exit(0);
}

/* main creates 2 threads for production and consumtion */
/* it initialises 3 semaphores, sync, delay_consumer and delay_producer */
/* it creates the threads and joins them together */
int main()
{
    pthread_t prod, cons;

	sem_init(&delay_producer, 0, 1);
    sem_init(&delay_consumer, 0, 0);
	sem_init(&sync, 0, 1);

	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);
	pthread_join(prod, NULL);
	pthread_join(cons, NULL);
	return 0;
}