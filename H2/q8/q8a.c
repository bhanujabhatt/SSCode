
/*
======================================================================================================================================================================
Name : q8.c
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
Triggering SIGSEGV (Segmentation Fault)...
Caught SIGSEGV: Segmentation Fault (signal 11)

======================================================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function for SIGSEGV
void handle_sigsegv(int sig) {
    printf("Caught SIGSEGV: Segmentation Fault (signal %d)\n", sig);
    exit(EXIT_FAILURE); // Exit after catching the signal
}

int main() {
    // Register signal handler for SIGSEGV
    signal(SIGSEGV, handle_sigsegv);

    printf("Triggering SIGSEGV (Segmentation Fault)...\n");

    // Trigger SIGSEGV by accessing invalid memory
    int *ptr = NULL;
    *ptr = 42;  // Dereferencing a NULL pointer will cause a segmentation fault

    return 0;
}

