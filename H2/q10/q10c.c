/*
======================================================================================================================================================================
Name : q10c.c
Author : BHANUJA BHATT
Description : Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE

Date: 7th sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Causing a floating-point exception (division by zero)...
Caught signal 8 (SIGFPE) due to a floating-point exception.
======================================================================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGFPE
void handle_sigfpe(int sig, siginfo_t *info, void *context) {
    printf("Caught signal %d (SIGFPE) due to a floating-point exception.\n", sig);
    exit(1); // Exit after catching the floating-point exception
}

int main() {
    struct sigaction sa_fpe;

    // Set up the SIGFPE handler
    sa_fpe.sa_sigaction = handle_sigfpe;
    sa_fpe.sa_flags = SA_SIGINFO; // Use SA_SIGINFO to get more detailed information about the signal
    sigemptyset(&sa_fpe.sa_mask); // Clear all signals from the mask

    if (sigaction(SIGFPE, &sa_fpe, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    // Deliberately cause a floating-point exception (SIGFPE)
    printf("Causing a floating-point exception (division by zero)...\n");
    int a = 5;
    int b = 0;
    int c = a / b; // This will cause SIGFPE

    // Wait indefinitely
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}

