/*
======================================================================================================================================================================
Name : q10b.c
Author : BHANUJA BHATT
Description : Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE

Date: 7th sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Running... Press Ctrl+C to trigger SIGINT
^CCaught signal 2 (SIGINT). Exiting gracefully.

======================================================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGINT
void handle_sigint(int sig) {
    printf("Caught signal %d (SIGINT). Exiting gracefully.\n", sig);
    exit(0); // Gracefully exit the program
}

int main() {
    struct sigaction sa_int;

    // Set up the SIGINT handler
    sa_int.sa_handler = handle_sigint;
    sa_int.sa_flags = 0; // No special flags
    sigemptyset(&sa_int.sa_mask); // Don't block additional signals during the handler

    if (sigaction(SIGINT, &sa_int, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    // Keep the program running to allow catching SIGINT
    printf("Running... Press Ctrl+C to trigger SIGINT\n");

    // Wait indefinitely
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}

