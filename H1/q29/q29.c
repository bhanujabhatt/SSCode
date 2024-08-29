/*
======================================================================================================================================================================
Name : handsonprog29.c
Author :Bhanuja Bhatt
Description : Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO, SCHED_RR).
Date: 28 aug, 2024
======================================================================================================================================================================
======================================================================================================================================================================
Sample Output:
sudo ./a.out
[sudo] password for bhanuja-bhatt: 
Policy used is standard round robin time sharing
Scheduling policy has been updated to real-time round robin, with priority 20


======================================================================================================================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/resource.h>

int main() {
    int policy;
    struct sched_param sp;
    sp.sched_priority = 20; // Set desired real-time priority

    // Get the current scheduling policy
    policy = sched_getscheduler(0);
    if (policy == -1) {
        perror("sched_getscheduler");
        return 1;
    }

    // Print the current scheduling policy
    switch (policy) {
        case SCHED_OTHER:
            printf("Policy used is standard round robin time sharing\n");
            break;
        case SCHED_FIFO:
            printf("Policy used is real time FIFO scheduling\n");
            break;
        case SCHED_RR:
            printf("Policy used is real time round robin scheduling\n");
            break;
        default:
            printf("Unknown scheduling policy\n");
            break;
    }

    // Attempt to set the scheduling policy to SCHED_RR
    int p = sched_setscheduler(0, SCHED_RR, &sp);
    if (p == -1) {
        perror("sched_setscheduler");
        return 1;
    }

    // Verify that the policy has been set
    if (sched_getscheduler(0) == SCHED_RR) {
        struct sched_param current_sp;
        sched_getparam(0, &current_sp);
        printf("Scheduling policy has been updated to real-time round robin, with priority %d\n", current_sp.sched_priority);
    }

    // Infinite loop to keep the process running
    for (;;);

    return 0;
}
