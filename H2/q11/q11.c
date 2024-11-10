
/*
======================================================================================================================================================================
Name : q11.c
Author : BHANUJA BHATT
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -
use sigaction system call.
Date: 8th sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
SIGINT (Ctrl+C) is ignored for the next 5 seconds. Try pressing Ctrl+C...
^CSIGINT is now handled. Press Ctrl+C again to reset to default behavior.
^CSIGINT ignored. Resetting to default behavior...
^C

======================================================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler to reset the SIGINT action to default
void reset_sigint(int sig) {
    printf("SIGINT ignored. Resetting to default behavior...\n");

    struct sigaction sa_default;
    sa_default.sa_handler = SIG_DFL; // Set the handler to the default action
    sa_default.sa_flags = 0;
    sigemptyset(&sa_default.sa_mask);

    if (sigaction(SIGINT, &sa_default, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
}

int main() {
    struct sigaction sa_ignore, sa_reset;

    // Set up the handler to ignore SIGINT
    sa_ignore.sa_handler = SIG_IGN; // Ignore the SIGINT signal
    sa_ignore.sa_flags = 0;
    sigemptyset(&sa_ignore.sa_mask);

    if (sigaction(SIGINT, &sa_ignore, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("SIGINT (Ctrl+C) is ignored for the next 5 seconds. Try pressing Ctrl+C...\n");
    sleep(5); // During this time, SIGINT is ignored

    // Set up the handler to reset SIGINT to its default behavior
    sa_reset.sa_handler = reset_sigint;
    sa_reset.sa_flags = 0;
    sigemptyset(&sa_reset.sa_mask);

    if (sigaction(SIGINT, &sa_reset, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("SIGINT is now handled. Press Ctrl+C again to reset to default behavior.\n");

    // Wait indefinitely to catch the second SIGINT signal
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}

