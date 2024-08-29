/*
======================================================================================================================================================================
Name : handsonprog28.c
Author : bhanuja bhatt
Description : Write a program to get maximum and minimum real time priority.
Date: 26 aug 2024
======================================================================================================================================================================
======================================================================================================================================================================
Sample Output:
Maximum real-time priority: 99
Minimum real-time priority: 1

======================================================================================================================================================================

*/
#include <stdio.h>
#include <sched.h>

int main() {
    int max_priority, min_priority;

    max_priority = sched_get_priority_max(SCHED_FIFO);
    min_priority = sched_get_priority_min(SCHED_FIFO);

    if (max_priority == -1 || min_priority == -1) {
        perror("sched_get_priority_max/min failed");
        return 1;
    }

    printf("Maximum real-time priority: %d\n", max_priority);
    printf("Minimum real-time priority: %d\n", min_priority);

    return 0;
}

