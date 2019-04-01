#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "linkedlist.h"
#include "coursework.h"


sem_t empty, full, sync;
pthread_t consumers[NUMBER_OF_CONSUMERS], producers[NUMBER_OF_PRODUCERS];

struct element *heads[MAX_PRIORITY];
struct element *tails[MAX_PRIORITY];

int produced, consumed;
int pID[NUMBER_OF_PRODUCERS], cID[NUMBER_OF_CONSUMERS];
double totalResponse = 0;
double totalTurnaround = 0;

/* turnAround function increments the global totalTurnaround variable which stores the total time for the processes to finish concurrently
    will print the output when a process has reached 0 iRemainingBurstTime
    it then frees the process
    increments the consumed counter storing number of processes consumed
    finally it sem_post() the empty semaphore so that producer() can produce more processes */
void turnAround(struct process *process, int timeDifference, int id)
{
    totalTurnaround += timeDifference;
    printf("Consumer Id = %d, Process ID = %d, Priortiy = %d, Previous Burst Time = %d, Remaining Burst Time = %d, Turnaround Time = %d\n", id, process->iProcessId, process->iPriority, process->iPreviousBurstTime, process->iRemainingBurstTime, timeDifference);
    free(process);
    consumed++; 
    sem_post(&empty);
}

/*  this function will print out the response time if its the first pass of the program
    it will also increment the global turnaround variable 
    otherwise it will just print out data about the process
    finally it will call sem_post() using &full as a parameter which signals that the process still needs to be consumed*/
void responseTime(struct process *process, int timeDifference, int id)
{
    if(process->iInitialBurstTime == process->iPreviousBurstTime)
        {
            totalResponse += timeDifference;
            printf("Consumer Id = %d, Process ID = %d, Priortiy = %d, Previous Burst Time = %d, Remaining Burst Time = %d, Response Time = %d\n", id, process->iProcessId, process->iPriority, process->iPreviousBurstTime, process->iRemainingBurstTime, timeDifference);
        }
    else
        printf("Consumer Id = %d, Process ID = %d, Priortiy = %d, Previous Burst Time = %d, Remaining Burst Time = %d\n", id, process->iProcessId, process->iPriority, process->iPreviousBurstTime, process->iRemainingBurstTime);
    sem_post(&full);
}

/* roundRobin function will call the runPreemptiveJob() function in coursework.c
    it checks if the process has reached 0 iRemainingBurstTime and if it hasnt it will open the critical section and add the process to the end of its respective priority queue
    it then calls the responseTime() function
    if iRemainingBurstTime is 0 for the process then it will call the turnAround() function */
void roundRobin(struct process * process, int id)
{
    struct timeval start, end;

    runPreemptiveJob(process, &start, &end);
    if(process->iRemainingBurstTime != 0)
    {
        sem_post(&sync);
        addLast(process, &heads[process->iPriority], &tails[process->iPriority]);   /* adds the current head to the end of the priority queue */
        sem_post(&sync);
        responseTime(process, getDifferenceInMilliSeconds(process->oTimeCreated, start), id);
    }

    else
        turnAround(process, getDifferenceInMilliSeconds(process->oTimeCreated, end), id);
}

/* producer function will iterate MAX_NUMBER_OF_JOBS times to generate a new process using generateProcess() implemented in coursework.c
    each process will enter the critical section where it will be added to the end of its respective priority queue
    if the number of produced processes exceeds or is equal to the MAX_NUMBER_OF_JOBS then it will break from the while loop otherwise it will increment the number of processes created variable
    it prints data about the new process which was created
    it calls the sem_post() function using &full as a parameter so that consumer() can carry on
    outside the while loop it closes the critical section and exits the thread */
void * producer(void * index)
{
    struct process *process;
    while(produced < MAX_NUMBER_OF_JOBS)
    {
        process = generateProcess();
        sem_wait(&empty);
        sem_wait(&sync);
        if(produced >= MAX_NUMBER_OF_JOBS)
            break;
        produced++;
        addLast(process, &heads[process->iPriority], &tails[process->iPriority]);
        sem_post(&sync);
        printf("Producer Id = %d, Items Produced = %d, New Process ID = %d, Burst Time = %d\n", *((int *) index) , produced, process->iProcessId, process->iInitialBurstTime);
        sem_post(&full);
        
    }
    sem_post(&sync);
    pthread_exit(0);
}

/* consumer() loops through all the processes which will be created
    it will open the critical section and remove the process of lowest priority
    it then closes the critical section and then calls roundRobin with the process as a parameter
    it will break the loop if  its consuming more processes that should exist
    exits  the threads and toggles the semaphores outisde of the while loop*/
void * consumer(void * index) {
    int lowestPriority;
    struct process *process;
    while(consumed < MAX_NUMBER_OF_JOBS)
    {
        sem_wait(&full);
        sem_wait(&sync);
        for(int i = 0; i < MAX_PRIORITY; i++)
            if(heads[i] != NULL)
            {
                lowestPriority = i;
                break;
            }
        if(consumed >= MAX_NUMBER_OF_JOBS)
            break;
        process = removeFirst(&heads[lowestPriority],&tails[lowestPriority]);   
        sem_post(&sync);
        roundRobin(process, *((int *) index));
    }
    sem_post(&sync);
    sem_post(&full);
    sem_post(&empty);
    pthread_exit(0);
}

/* main initialiases all the semaphores, the priority queues and the producer and consumers
    it creates a thread for each producer and consumer created
    it joins all the threads at after they have all been created
    finally it prints the average response time and average turn around time at the end of the program */
int main(int argc, char const *argv[])
{
    sem_init(&full, 0, 0); 
    sem_init(&empty, 0, MAX_BUFFER_SIZE);
    sem_init(&sync, 0, 1);

    for(int i = 0; i < MAX_PRIORITY; i++)
        heads[i] = tails[i] = NULL;

    for(int i = 0; i < NUMBER_OF_PRODUCERS; i++)
        pID[i] = i;
    for(int i = 0; i < NUMBER_OF_CONSUMERS; i++)
        cID[i] = i;
    

    for (int i=0; i<NUMBER_OF_PRODUCERS; i++) 
        pthread_create(&producers[i], NULL, producer, (void *) &pID[i]);
    for (int i=0; i<NUMBER_OF_CONSUMERS; i++)
        pthread_create(&consumers[i], NULL, consumer, (void *) &cID[i]);

    for (int i=0; i<NUMBER_OF_PRODUCERS; i++)
        pthread_join(producers[i],NULL);
    for (int i=0; i<NUMBER_OF_CONSUMERS; i++)
        pthread_join(consumers[i],NULL);  

    printf("Average response time = %f\nAverage turn around time = %f\n", (totalResponse) / MAX_NUMBER_OF_JOBS, totalTurnaround / MAX_NUMBER_OF_JOBS);
    return 0;
}