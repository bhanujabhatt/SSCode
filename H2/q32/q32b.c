#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>

#define SHM_SIZE sizeof(int)  // Shared memory size

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

    // Create shared memory segment
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory
    int *ticketno = (int *)shmat(shmid, NULL, 0);
    if (ticketno == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Create semaphore
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphore to 1
    union semun sem_attr;
    sem_attr.val = 1;
    if (semctl(semid, 0, SETVAL, sem_attr) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    // Lock semaphore before critical section
    struct sembuf sem_lock = {0, -1, SEM_UNDO};
    if (semop(semid, &sem_lock, 1) == -1) {
        perror("semop lock");
        exit(EXIT_FAILURE);
    }

    // Critical section: Read and increment shared memory ticket number
    (*ticketno)++;
    printf("New ticket number: %d\n", *ticketno);

    // Unlock semaphore after critical section
    struct sembuf sem_unlock = {0, 1, SEM_UNDO};
    if (semop(semid, &sem_unlock, 1) == -1) {
        perror("semop unlock");
        exit(EXIT_FAILURE);
    }

    // Detach shared memory
    if (shmdt(ticketno) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    return 0;
}

