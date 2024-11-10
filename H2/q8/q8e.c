

/*
======================================================================================================================================================================
Name : q8e.c
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

Timer set: Initial expiration in 2 seconds, then every 3 seconds.
Caught SIGALRM (signal 14): Timer went off!
Caught SIGALRM (signal 14): Timer went off!
Caught SIGALRM (signal 14): Timer went off!

======================================================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

// Signal handler function for SIGALRM
void handle_sigalrm(int sig) {
    printf("Caught SIGALRM (signal %d): Timer went off!\n", sig);
}

int main() {
    struct itimerval timer;

    // Register signal handler for SIGALRM
    signal(SIGALRM, handle_sigalrm);

    // Configure the timer to expire after 2 seconds
    timer.it_value.tv_sec = 2;  // Initial delay (seconds)
    timer.it_value.tv_usec = 0; // Initial delay (microseconds)

    // Configure the timer to repeat every 3 seconds after the initial expiration
    timer.it_interval.tv_sec = 3;  // Interval between subsequent signals (seconds)
    timer.it_interval.tv_usec = 0; // Interval between subsequent signals (microseconds)

    // Set the timer with setitimer, specifying that it will use the real-time clock (ITIMER_REAL)
    setitimer(ITIMER_REAL, &timer, NULL);

    // Inform the user about the timer
    printf("Timer set: Initial expiration in 2 seconds, then every 3 seconds.\n");

    // Wait for signals to be delivered
    while (1) {
        pause();  // Suspend the program until a signal is caught
    }

    return 0;
}

