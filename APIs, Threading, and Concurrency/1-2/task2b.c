#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "coursework.h" 

/*  global variables storing the total reponse and turnaround time from running the first program */
double totalResponse = 0;
double totalTurnaround = 0;

/*  this function will print out the turn around time and increment the global turnaround variable 
    it also frees the  process because it has reached 0 iRemainingBurstTime*/
void turnAround(struct process *process, int timeDifference)
{
    totalTurnaround += timeDifference;
    printf(", Turnaround Time = %d\n", timeDifference);
    free(process);
}

/*  this function will print out the response time if its the first pass of the program
    it will also increment the global turnaround variable */
void responseTime(struct process *process, int timeDifference)
{
    if(process->iInitialBurstTime == process->iPreviousBurstTime)
    {
        totalResponse += timeDifference;
        printf(", Response Time = %d", timeDifference);
    }
    printf("\n");
}

/*  this function will run each program until there is iRemainingBurstTime is equal to 0
    it is called recursively for priority queues with more than one element
    otherwise it will use a while loop to run processes with only one element */
void roundRobin(struct element * pHead, struct element * pTail)
{
    struct timeval start, end;
    struct element * pNext = pHead->pNext;  /* temporarily storing the element which pHead points to */
    struct process * process = (struct process *) removeFirst(&pHead, &pTail);  /* storing the process currently in the head */

    /*  if there is only one element in the list it runs it until it reaches 0 iRemainingBurstTime */
    if(!pNext)
    {
        while(process->iRemainingBurstTime != 0)
        {
            runPreemptiveJob(process, &start, &end);    /* runs the job in coursework.c */
            printf("Process Id = %d, Priortiy = %d, Previous Burst Time = %d, Remaining Burst Time = %d", process->iProcessId, process->iPriority, process->iPreviousBurstTime, process->iRemainingBurstTime);
            if(process->iRemainingBurstTime != 0)
                responseTime(process, getDifferenceInMilliSeconds(process->oTimeCreated, start));
        }
        turnAround(process, getDifferenceInMilliSeconds(process->oTimeCreated, end));
    }
    /* separate implementation for prioirty queue with more than one element */
    else
    {
        runPreemptiveJob(process, &start, &end);
        printf("Process Id = %d, Priortiy = %d, Previous Burst Time = %d, Remaining Burst Time = %d", process->iProcessId, process->iPriority, process->iPreviousBurstTime, process->iRemainingBurstTime);
        if(process->iRemainingBurstTime != 0)
        {
            responseTime(process, getDifferenceInMilliSeconds(process->oTimeCreated, start));
            addLast(process, &pHead, &pTail);   /* adds the current head to the end of the priority queue */
        }
        else if(process->iRemainingBurstTime == 0)
            turnAround(process, getDifferenceInMilliSeconds(process->oTimeCreated, end));
        roundRobin(pNext, pTail);   /* recursively calls roundRobin with the new head and tail */
    }
}

/* this function will print the process data for each process in each priority list */
void printList(struct element * pHead)
{
    struct element *currentElement = pHead;
    while(currentElement != NULL)
    {
        struct process *process = currentElement->pData;
        printf("\tProcess Id = %d, Priority = %d, Initial Burst Time = %d, Remaining Burst Time = %d\n", process->iProcessId, process->iPriority, process->iInitialBurstTime, process->iRemainingBurstTime);
        currentElement = currentElement->pNext;
    }
}


int main(int argc, char const *argv[])
{
    struct element *head = NULL;
    struct element *tail = NULL;
    struct element *heads[MAX_PRIORITY]; /* list of all possible priorities */
    struct element *tails[MAX_PRIORITY];

    /* populating priorities list */
    for(int i = 0; i < MAX_PRIORITY; i++)
        heads[i] = tails[i] = NULL;
    
    /* populating initial list of intial processes */
    for(int i = 0; i < MAX_NUMBER_OF_JOBS; i++)
        addLast(generateProcess(), &head, &tail);

    /* appending processes to the index equal to their priority */
    for(int i = 0; i < MAX_NUMBER_OF_JOBS; i++)
    { 
        struct process *process = (struct process *) removeFirst(&head, &tail);
        addLast((void *)process, &heads[process->iPriority], &tails[process->iPriority]); 
    }

    /* printing the ordered process list */
    printf("PROCESS LIST:\n");
    for(int i = 0; i < MAX_PRIORITY; i++)
    {
        if(heads[i] != NULL)
        {
            printf("Priority: %d\n", i);
            printList(heads[i]);
        }
    }
    printf("END\n\n");

    /* executes each job until all processes terminate */
    for(int i = 0; i < MAX_PRIORITY; i++)
    {
        if(heads[i] != NULL)
            roundRobin(heads[i], tails[i]);
    }

    /* print the average response and turnaround global variables as an average */
    printf("Average response time = %f\nAverage turn around time = %f\n", (totalResponse) / MAX_NUMBER_OF_JOBS, totalTurnaround / MAX_NUMBER_OF_JOBS);
    return 0;
}