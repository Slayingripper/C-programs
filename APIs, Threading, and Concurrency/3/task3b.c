#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "linkedlist.h"
#include "coursework.h"

sem_t empty, full, sync;
pthread_t consumers[NUMBER_OF_CONSUMERS], producers[NUMBER_OF_PRODUCERS];

struct element *head = NULL;
struct element *tail = NULL;

int produced, consumed, itemCounter = 0;
int pID[NUMBER_OF_PRODUCERS], cID[NUMBER_OF_CONSUMERS];

/* printProcess will take either "Producer" or "Consumer" and the index of the respective process as a parameter */
/* it prints the type of process, index of current process and how many processes have been consumed or produced */
/* finally it will print the number of stars corresponding to processes in the buffer */
void printProcesses(char process[9], int index)
{
    printf("%s Id = %d, Produced = %d, Consumed = %d: ", process, index , produced, consumed);
    for(int i = 0; i < itemCounter; i++)
        printf("*");
    printf("\n");
    return;
}


/* producer method loops through the MAX_NUMBER_OF_JOBS */
/* it will enter the critical section and add a process using generateProcess() to the end of the buffer */
/* next it prints data about how many processes have been consumed and produced with the ID of the current producer */
/* finally it leaves the critical section */
/* outside of the while loop it will destroy the threads when its finished by using pthread_cancel() on the producers */
void * producer(void * index)
{
    while(produced < MAX_NUMBER_OF_JOBS)
    {
        sem_wait(&empty);
        sem_wait(&sync);
        if(produced >= MAX_NUMBER_OF_JOBS)  /* prevents slept consumers from over production */
            break;
        addLast(generateProcess(), &head, &tail);
        itemCounter++;
        produced++;
        printProcesses("Producer\0", *((int *) index));
        sem_post(&sync);
        sem_post(&full);
    }
   
    /* posts full and sync if the while loop breaks early  */
    sem_post(&sync);
    sem_post(&full);
	sem_post(&empty);
    return 0;
}

/* consumer method loops through the MAX_NUMBER_OF_JOBS */
/* it will enter the critical section and free the process after calling removeFirst() */
/* next it prints data about how many processes have been consumed and produced with the ID of the current consumer */
/* finally it leaves the critical section */
/* outside of the while loop it will destroy the threads when its finished by using pthread_cancel() on the producers */
void * consumer(void * index) {
    while(consumed < MAX_NUMBER_OF_JOBS)
    {
        sem_wait(&full);
        sem_wait(&sync);
        /* prevents slept consumers from over consumption */
        if(consumed >= MAX_NUMBER_OF_JOBS)
            break;
        free(removeFirst(&head,&tail));
        itemCounter--;
        consumed++;
        printProcesses("Consumer\0", *((int *) index));
        sem_post(&sync);
        sem_post(&empty);   
		sem_post(&full);
    }
    
    /* posts sync and empty if the while loop breaks early  */
    sem_post(&sync);   
    sem_post(&empty);  
    return 0;
}

/* main populates the producer and consumer ID arrays */
/* it then calls sem_init for the sync, full and empty semaphores  */
/* main will then iterate through number of producers and consumers and calls pthread_create() passing the index of the producer or consumer as a casted void ptr */
/* finally main will join the producers and consumers */
int main(){
    for(int i = 0; i < NUMBER_OF_PRODUCERS; i++)
        pID[i] = i;
    for(int i = 0; i < NUMBER_OF_CONSUMERS; i++)
        cID[i] = i;
    sem_init(&full, 0, 0); 
    sem_init(&empty, 0, MAX_BUFFER_SIZE);
    sem_init(&sync, 0, 1); 

    /* create threads for producer and consumers */
    for (int i=0; i<NUMBER_OF_PRODUCERS; i++) 
        pthread_create(&producers[i], NULL, producer, (void *) &pID[i]);
    for (int i=0; i<NUMBER_OF_CONSUMERS; i++)
        pthread_create(&consumers[i], NULL, consumer, (void *) &cID[i]);

    /* join producers and consumers */
    for (int i=0; i<NUMBER_OF_PRODUCERS; i++)
        pthread_join(producers[i],NULL);
    for (int i=0; i<NUMBER_OF_CONSUMERS; i++)
        pthread_join(consumers[i],NULL);  
}
