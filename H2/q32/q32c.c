#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
};

int main() {
    key_t key = ftok("ticket.txt", 'b');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a semaphore set with two semaphores (for two pseudo resources)
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize the counting semaphore to 2 (both resources available)
    union semun sem_attr;
    sem_attr.val = 2; // 2 resources available
    if (semctl(semid, 0, SETVAL, sem_attr) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    // Lock semaphore before accessing a resource
    struct sembuf sem_lock = {0, -1, SEM_UNDO};
    if (semop(semid, &sem_lock, 1) == -1) {
        perror("semop lock");
        exit(EXIT_FAILURE);
    }

    // Simulate resource usage
    printf("Resource is being used by the process\n");
    sleep(3);  // Simulate some work with the resource

    // Unlock semaphore after releasing the resource
    struct sembuf sem_unlock = {0, 1, SEM_UNDO};
    if (semop(semid, &sem_unlock, 1) == -1) {
        perror("semop unlock");
        exit(EXIT_FAILURE);
    }

    printf("Resource released\n");

    return 0;
}

