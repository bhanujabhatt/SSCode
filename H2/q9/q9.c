
Name : q9.c
Author : BHANUJA BHATT
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
Date: 14 sept, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
SIGINT signal is now ignored.
Waiting for 5 seconds. Try pressing Ctrl+C during this time...
^CSIGINT signal action reset to default.
Waiting for another 5 seconds. Try pressing Ctrl+C during this time...
^C

======================================================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler to demonstrate signal handling
void signal_handler(int sig) {
    printf("Caught signal %d\n", sig);
}

int main() {
    // Ignore SIGINT
    signal(SIGINT, SIG_IGN);
    printf("SIGINT signal is now ignored.\n");

    // Wait for 5 seconds to demonstrate ignoring SIGINT
    printf("Waiting for 5 seconds. Try pressing Ctrl+C during this time...\n");
    sleep(5);

    // Reset SIGINT to default action
    signal(SIGINT, SIG_DFL);
    printf("SIGINT signal action reset to default.\n");


    // Wait again to demonstrate default action
    printf("Waiting for another 5 seconds. Try pressing Ctrl+C during this time...\n");
    sleep(5);

    // If SIGINT is received, it will terminate the program with default action
    return 0;
}
