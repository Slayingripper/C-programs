#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "coursework.h" 

int main(int argc, char const *argv[])
{
    struct element *head = NULL;
    struct element *tail = NULL;
    struct timeval start, end;
    double responseTime = 0;
    double turnAroundTime = 0;

    for(int i = 0; i < MAX_NUMBER_OF_JOBS; i++)
        addLast(generateProcess(), &head, &tail);   /* generate a new process and add it to the end of the list */

    for(int i = 0; i < MAX_NUMBER_OF_JOBS; i++)
    {
        struct process *process = (struct process *) removeFirst(&head, &tail); /* remove the head and store the process in a pointer variable */
        runNonPreemptiveJob(process, &start, &end); /* run the job */
        printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %ld, Turn Around Time = %ld\n", process->iProcessId, process->iPreviousBurstTime, process->iRemainingBurstTime, getDifferenceInMilliSeconds(process->oTimeCreated, start), getDifferenceInMilliSeconds(process->oTimeCreated, end));
        /* total response and turnaround time to calculate averages later */
        responseTime += getDifferenceInMilliSeconds(process->oTimeCreated, start);
        turnAroundTime += getDifferenceInMilliSeconds(process->oTimeCreated, end);
        free(process);  /* frees the current process at the head of the list */
    }
    /* print average response and turnaround times */
    printf("Average response time = %f\nAverage turn around time = %f\n", responseTime / MAX_NUMBER_OF_JOBS, turnAroundTime / MAX_NUMBER_OF_JOBS);
    return 0;
}
 