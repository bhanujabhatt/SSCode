/*
======================================================================================================================================================================
Name : q10a.c
Author : BHANUJA BHATT
Description : Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE

Date: 7th sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Causing a segmentation fault...
Caught signal 11 (SIGSEGV) at address: (nil)
======================================================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

// Signal handler for SIGSEGV
void handle_sigsegv(int sig, siginfo_t *info, void *context) {
    printf("Caught signal %d (SIGSEGV) at address: %p\n", sig, info->si_addr);
    exit(1); // Exit after catching the segmentation fault
}

int main() {
    struct sigaction sa_segv;

    // Set up the SIGSEGV handler
    memset(&sa_segv, 0, sizeof(sa_segv));
    sa_segv.sa_sigaction = handle_sigsegv;
    sa_segv.sa_flags = SA_SIGINFO; // Use SA_SIGINFO to get more detailed information about the signal

    if (sigaction(SIGSEGV, &sa_segv, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    // Deliberately cause a segmentation fault (SIGSEGV)
    printf("Causing a segmentation fault...\n");
    int *ptr = NULL;
    *ptr = 42; // This will cause SIGSEGV

    // Wait indefinitely
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}

