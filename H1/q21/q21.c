/*
======================================================================================================================================================================
Name : handsonprog21.c
Author :Bhanuja Bhatt
Description : Write a program, call fork and print the parent and child process id.
Date:21st aug, 2024
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Parent process:
Parent PID: 109338
Child PID: 109339
Child process:
Child PID: 109339
Parent PID: 109338


======================================================================================================================================================================
*/
#include <stdio.h>
#include <unistd.h>  
#include <sys/types.h> 

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        printf("Child process:\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    } else {
        printf("Parent process:\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
    }

    return 0;
}

