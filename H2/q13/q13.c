/*
======================================================================================================================================================================
Name :q13a.c
Author : BHANUJA BHATT
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not.
Date: 19th sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Waiting for signals (Process ID: 8864)...

[1]+  Stopped                 ./a.out
bhanuja-bhatt@bhanuja-bhatt-HP-Laptop:~/my-repo2/H2/q13$ Caught signal SIGUSR1 (signal number: 10)

======================================================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function for SIGUSR1
void sigusr1_handler(int signum) {
    printf("Caught signal SIGUSR1 (signal number: %d)\n", signum);
}

// Signal handler function for SIGSTOP (This won't work)
void sigstop_handler(int signum) {
    // Remove the format specifier since this won't be called
    printf("Caught signal SIGSTOP - This won't be printed.\n");
}

int main() {
    // Set up signal handler for SIGUSR1
    signal(SIGUSR1, sigusr1_handler);

    // Attempt to catch SIGSTOP (this won't work)
    signal(SIGSTOP, sigstop_handler);  // This will have no effect

    printf("Waiting for signals (Process ID: %d)...\n", getpid());

    // Infinite loop to keep the program running
    while (1) {
        pause();  // Wait for signals
    }

    return 0;
}

