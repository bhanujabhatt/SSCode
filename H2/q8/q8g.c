
/*
======================================================================================================================================================================
Name : q8g.c
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
Profiling timer set: Program will receive SIGPROF after 2 seconds of total CPU time.
Caught SIGPROF (signal 27): Profiling timer went off!
Caught SIGPROF (signal 27): Profiling timer went off!

======================================================================================================================================================================
*/#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

// Signal handler for SIGPROF
void handle_sigprof(int sig) {
    printf("Caught SIGPROF (signal %d): Profiling timer went off!\n", sig);
}

int main() {
    struct itimerval timer;

    // Register signal handler for SIGPROF
    signal(SIGPROF, handle_sigprof);

    // Configure the timer to expire after 2 seconds of total CPU time (user + system)
    timer.it_value.tv_sec = 2;    // Initial expiration after 2 seconds
    timer.it_value.tv_usec = 0;   // Initial expiration microseconds

    // Configure the timer to repeat every 2 seconds of total CPU time
    timer.it_interval.tv_sec = 2; // Interval of 2 seconds between signals
    timer.it_interval.tv_usec = 0;

    // Set the profiling timer using ITIMER_PROF
    setitimer(ITIMER_PROF, &timer, NULL);

    // Inform the user about the timer
    printf("Profiling timer set: Program will receive SIGPROF after 2 seconds of total CPU time.\n");

    // Simulate some work to use up CPU time
    while (1) {
        // Simulate CPU-bound work to accumulate CPU time
        for (volatile long i = 0; i < 100000000; i++);
    }

    return 0;
}

