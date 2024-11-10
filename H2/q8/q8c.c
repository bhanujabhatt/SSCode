
/*
======================================================================================================================================================================
Name : q8c.c
Author : BHANUJA BHATT
Description :. Write a separate program using signal system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
d. SIGALRM (use alarm system call)
e. SIGALRM (use setitimer system call)
f. SIGVTALRM (use setitimer system call)
g. SIGPROF (use setitimer system call)
Date: 14 sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output
Triggering SIGFPE by dividing by zero...
Caught SIGFPE (signal 8): Floating-point exception
Exiting due to floating-point error...


======================================================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Signal handler function for SIGFPE
void handle_sigfpe(int sig) {
    printf("Caught SIGFPE (signal %d): Floating-point exception\n", sig);
    printf("Exiting due to floating-point error...\n");
    exit(EXIT_FAILURE); // Exit after handling the signal
}

int main() {
    // Register signal handler for SIGFPE
    signal(SIGFPE, handle_sigfpe);

    // Trigger SIGFPE: Floating-point exception (division by zero)
    printf("Triggering SIGFPE by dividing by zero...\n");
    int x = 1;
    int y = 0;
    int result = x / y; // This will cause a division by zero and trigger SIGFPE

    // The program won't reach here due to the floating-point exception
    printf("Result: %d\n", result);

    return 0;
}

