
/*
======================================================================================================================================================================
Name : q13b.c
Author : BHANUJA BHATT
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not.
Date: 19th sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
bhanuja-bhatt@bhanuja-bhatt-HP-Laptop:~/my-repo2/H2/q13$ ./a.out
Enter the PID of the process to send signals to: 8864
Sending SIGUSR1 to process 8864
Sending SIGSTOP to process 8864
Sending SIGCONT to process 8864

======================================================================================================================================================================
*/
// sigstop_sender.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // Ask the user for the PID of the first program
    printf("Enter the PID of the process to send signals to: ");
    scanf("%d", &pid);

    // Send SIGUSR1 first (this will be caught)
    printf("Sending SIGUSR1 to process %d\n", pid);
    kill(pid, SIGUSR1);  // Send SIGUSR1

    // Send SIGSTOP (this will stop the process but won't be caught)
    printf("Sending SIGSTOP to process %d\n", pid);
    kill(pid, SIGSTOP);  // Send SIGSTOP (this will stop the process)

    // Sleep for a few seconds to observe that the first program has stopped
    sleep(5);

    // Send SIGCONT to resume the first process
    printf("Sending SIGCONT to process %d\n", pid);
    kill(pid, SIGCONT);  // Resume the stopped process

    return 0;
}

