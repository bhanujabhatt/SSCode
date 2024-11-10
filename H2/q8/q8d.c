
/*
======================================================================================================================================================================
Name : q8d.c
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
Setting an alarm for 5 seconds...
Waiting for the alarm...
Caught SIGALRM (signal 14): Alarm went off!
Exiting after receiving the alarm...


======================================================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function for SIGALRM
void handle_sigalrm(int sig) {
    printf("Caught SIGALRM (signal %d): Alarm went off!\n", sig);
    printf("Exiting after receiving the alarm...\n");
    exit(EXIT_SUCCESS); // Exit the program after handling the signal
}

int main() {
    // Register signal handler for SIGALRM
    signal(SIGALRM, handle_sigalrm);

    // Set an alarm to trigger SIGALRM after 5 seconds
    printf("Setting an alarm for 5 seconds...\n");
    alarm(5);

    // Wait for the alarm signal
    printf("Waiting for the alarm...\n");
    pause();  // pause() suspends the program until a signal is received

    // This line will not be reached because the program will exit in the handler
    return 0;
}

