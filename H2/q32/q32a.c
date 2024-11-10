/*
==================================================================================================================================================================================
Name : handsonprog32a.c
Author : BHANUJA BHATT
Description : Write a program to implement semaphore to protect any critical section.
		a. rewrite the ticket number creation program using semaphore
		b. protect shared memory from concurrent write access
		c. protect multiple pseudo resources ( may be two) using counting semaphore
		d. remove the created semaphore
Date: 10th sep, 2024
==================================================================================================================================================================================
==================================================================================================================================================================================
Sample Output:
$ ./book_ticket 
Before entering into critical section..
Inside the critical section...
Current ticket number: 9
Press enter to unlock and exit

./book_ticket 
Before entering into critical section..
==================================================================================================================================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>

// Union required for semctl
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
};

int main() {
    int ticketno;
    int fd = open("ticket.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening ticket.txt");
        exit(EXIT_FAILURE);
    }

    // Create a semaphore
    key_t key = ftok("ticket.txt", 'b');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize the semaphore to 1 (unlocked state)
    union semun sem_attr;
    sem_attr.val = 1;
    if (semctl(semid, 0, SETVAL, sem_attr) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    // Lock semaphore before entering critical section
    struct sembuf sem_lock = {0, -1, SEM_UNDO};
    if (semop(semid, &sem_lock, 1) == -1) {
        perror("semop lock");
        exit(EXIT_FAILURE);
    }

    // Critical section: Read and increment ticket number
    read(fd, &ticketno, sizeof(ticketno));
    ticketno++;
    lseek(fd, 0, SEEK_SET);
    write(fd, &ticketno, sizeof(ticketno));
    printf("New ticket number: %d\n", ticketno);

    // Unlock semaphore after leaving critical section
    struct sembuf sem_unlock = {0, 1, SEM_UNDO};
    if (semop(semid, &sem_unlock, 1) == -1) {
        perror("semop unlock");
        exit(EXIT_FAILURE);
    }

    close(fd);
    return 0;  // Ensure the function closes properly
}

   

