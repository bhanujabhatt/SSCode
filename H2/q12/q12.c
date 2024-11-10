
/*
======================================================================================================================================================================
Name : handsonprog12.c
Author : BHANUJA BHATT
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
the parent process from the child process.
Date: 15th sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Parent process (PID: 8726)
Child process started (PID: 8727, Parent PID: 8726)
Child sending SIGKILL to parent (PID: 8726)
Killed
bhanuja-bhatt@bhanuja-bhatt-HP-Laptop:~/my-repo2/H2/q12$ Child is now an orphan and is adopted by init/systemd (Parent PID: 1779)
======================================================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("Child process started (PID: %d, Parent PID: %d)\n", getpid(), getppid());
        sleep(2); // Sleep for a bit to allow the parent to run
        
        // Send SIGKILL to the parent process
        printf("Child sending SIGKILL to parent (PID: %d)\n", getppid());
        kill(getppid(), SIGKILL);  // Send SIGKILL signal to parent

        // Sleep for a bit to show the child is still running as an orphan
        sleep(5);
        printf("Child is now an orphan and is adopted by init/systemd (Parent PID: %d)\n", getppid());

        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        printf("Parent process (PID: %d)\n", getpid());
        sleep(10); // Keep parent alive longer than the child expects
        printf("Parent still alive\n");
    }

    return 0;
}
