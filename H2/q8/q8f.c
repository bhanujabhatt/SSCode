
/*
======================================================================================================================================================================
Name : q8f.c
Author : BHANUJA BHATT
Description :. Write a separate program using signal system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
d. SIGALRM (use alarm system call)
e. SIGALRM (use setitimer system call)
f. SIGVTALRM (use setitimer system call)
g. SIGPROF (use setitimer system call)
Date: 13 sept, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output
Virtual timer set: Program will receive SIGVTALRM after 1 second of CPU time.
Caught SIGVTALRM (signal 26): Virtual timer went off!
Caught SIGVTALRM (signal 26): Virtual timer went off!
Caught SIGVTALRM (signal 26): Virtual timer went off!
Caught SIGVTALRM (signal 26): Virtual timer went off!
Caught SIGVTALRM (signal 26): Virtual timer went off!
Caught SIGVTALRM (signal 26): Virtual timer went off!
Caught SIGVTALRM (signal 26): Virtual timer went off!
Caught SIGVTALRM (signal 26): Virtual timer went off!
Caught SIGVTALRM (signal 26): Virtual timer went off!


======================================================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

// Signal handler for SIGVTALRM
void handle_sigvtalrm(int sig) {
    printf("Caught SIGVTALRM (signal %d): Virtual timer went off!\n", sig);
}

int main() {
    struct itimerval timer;

    // Register signal handler for SIGVTALRM
    signal(SIGVTALRM, handle_sigvtalrm);

    // Configure the timer to expire after 1 second of CPU time
    timer.it_value.tv_sec = 1;    // Initial expiration after 1 second
    timer.it_value.tv_usec = 0;   // Initial expiration microseconds

    // Configure the timer to repeat every 1 second of CPU time
    timer.it_interval.tv_sec = 1; // Interval of 1 second between signals
    timer.it_interval.tv_usec = 0;

    // Set the virtual timer using ITIMER_VIRTUAL
    setitimer(ITIMER_VIRTUAL, &timer, NULL);

    // Simulate some work to use up CPU time
    printf("Virtual timer set: Program will receive SIGVTALRM after 1 second of CPU time.\n");

    // Keep the program running and consuming CPU time to trigger the timer
    while (1) {
        // Simulate CPU-bound work to accumulate CPU time
        for (volatile long i = 0; i < 100000000; i++);
    }

    return 0;
}

