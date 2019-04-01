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

int produced, consumed;
int pID[NUMBER_OF_PRODUCERS], cID[NUMBER_OF_CONSUMERS];
double totalResponse = 0;
double totalTurnaround = 0;


/* runJob function will call the runNonPreemptiveJob from coursework.c
    it increments the gloval totalResponse and totalTurnAround variables using the function getDifferenceInMilliseconds() from coursework.c
    which returns and interger value from when the process was created until the respective start/end
    it then prints data about the consumed process
    finally it frees the process */
void runJob(struct process * process, int id) 
{    
    struct timeval start,end;
    runNonPreemptiveJob(process, &start, &end);
    totalResponse += getDifferenceInMilliSeconds(process->oTimeCreated, start);
    totalTurnaround += getDifferenceInMilliSeconds(process->oTimeCreated, end);
    printf("Consumer Id: %d, Process ID: %d, Previous Burst Time = %d, New Burst Time = %d, Response time: %ld, Turnaround time: %ld\n",id,process->iProcessId,process->iPreviousBurstTime, process->iRemainingBurstTime , getDifferenceInMilliSeconds(process->oTimeCreated, start),getDifferenceInMilliSeconds(process->oTimeCreated, end));
    free(process);
}

/* producer function will iterate MAX_NUMBER_OF_JOBS times to generate a new process using generateProcess() implemented in coursework.c inside of the critical section
    each process will enter the critical section where it will be added to the end of of the list
    if the number of produced processes exceeds or is equal to the MAX_NUMBER_OF_JOBS then it will break from the while loop otherwise it will increment the number of processes created variable
    it prints data about the new process which was created
    it calls the sem_post() function using &full as a parameter so that consumer() can carry on
    outside the while loop it closes the critical section and exits the thread */
void * producer(void * index)
{
    while(produced < MAX_NUMBER_OF_JOBS)
    {
        sem_wait(&empty);
        sem_wait(&sync);
        if(produced >= MAX_NUMBER_OF_JOBS)
            break;
        struct process *process = generateProcess();
        produced++;
        addLast(process, &head, &tail);
        sem_post(&sync);
        sem_post(&full);
        printf("Process Id = %d, Items Produced = %d, New Process ID = %d, Burst Time = %d\n", *((int *) index) , produced, process->iProcessId, process->iInitialBurstTime);
    }
    sem_post(&sync);
    sem_post(&full);
    sem_post(&empty);
    pthread_exit(0);
}

/* consumer() loops through all the processes which will be created
    it will open the critical section to remove the head of the list
    it then increments the counter which counts number of processes consumed
    it will break the loop if  its consuming more processes that should exist
    when it clsoes the critical section it calls the runJob() function passing the process as a parameter
    exits  the threads and toggles the semaphores outisde of the while loop*/
void * consumer(void * index) {
    while(consumed < MAX_NUMBER_OF_JOBS)
    {   
        sem_wait(&full);
        sem_wait(&sync);
        if(consumed >= MAX_NUMBER_OF_JOBS)
            break;
        struct process *process = removeFirst(&head,&tail);
        consumed++;
        sem_post(&sync);
        sem_post(&empty);    
        runJob(process, *((int *) index));
    }
    sem_post(&sync);   
    sem_post(&empty);
    sem_post(&full);
    pthread_exit(0);
}

/* main initialiases all the semaphores, the priority queues and the producer and consumers
    it creates a thread for each producer and consumer created
    it joins all the threads at after they have all been created
    finally it prints the average response time and average turn around time at the end of the program */
int main(){
    for(int i = 0; i < NUMBER_OF_PRODUCERS; i++)
        pID[i] = i;
    for(int i = 0; i < NUMBER_OF_CONSUMERS; i++)
        cID[i] = i;
    sem_init(&full, 0, 0); 
    sem_init(&empty, 0, MAX_BUFFER_SIZE);
    sem_init(&sync, 0, 1); 

    for (int i=0; i<NUMBER_OF_PRODUCERS; i++) 
        pthread_create(&producers[i], NULL, producer, (void *) &pID[i]);
    for (int i=0; i<NUMBER_OF_CONSUMERS; i++)
        pthread_create(&consumers[i], NULL, consumer, (void *) &cID[i]);

    for (int i=0; i<NUMBER_OF_PRODUCERS; i++)
        pthread_join(producers[i],NULL);
    for (int i=0; i<NUMBER_OF_CONSUMERS; i++)
        pthread_join(consumers[i],NULL);  

    printf("Average response time = %f\nAverage turn around time = %f\n", totalResponse / MAX_NUMBER_OF_JOBS, totalTurnaround / MAX_NUMBER_OF_JOBS);
}