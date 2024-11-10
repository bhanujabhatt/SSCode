
/*
======================================================================================================================================================================
Name : q8b.c
Author : BHANUJA BHATT
Description :. Write a separate program using signal system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
d. SIGALRM (use alarm system call)
e. SIGALRM (use setitimer system call)
f. SIGVTALRM (use setitimer system call)
g. SIGPROF (use setitimer system call)
Date: 13 sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output
Program is running. Press Ctrl + C to trigger SIGINT...
^CCaught SIGINT (signal 2): Interrupt signal (Ctrl + C)
Exiting gracefully...

======================================================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function for SIGINT
void handle_sigint(int sig) {
    printf("Caught SIGINT (signal %d): Interrupt signal (Ctrl + C)\n", sig);
    printf("Exiting gracefully...\n");
    exit(EXIT_SUCCESS); // Exit the program gracefully after handling the signal
}

int main() {
    // Register signal handler for SIGINT
    signal(SIGINT, handle_sigint);

    // Infinite loop to keep the program running
    printf("Program is running. Press Ctrl + C to trigger SIGINT...\n");
    while (1) {
        sleep(1);  // Sleep for 1 second in each iteration to simulate a long-running process
    }

    return 0;
}

