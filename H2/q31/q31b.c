/*
======================================================================================================================================================================
Name : q31.c
Author : BHANUJA BHATT
Description : Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
Date: 14 sept, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Counting semaphore created successfully

======================================================================================================================================================================
*/
#include <unistd.h> 
#include <unistd.h> 

#include <stdio.h>

#include <sys/sem.h>

#include <sys/ipc.h>

#include <sys/types.h>

#include <sys/time.h> 

#include <time.h>

union semun{
	int val;    /* Value for SETVAL */
       	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
       	unsigned short int *array;
};

int main(){
	int key = ftok(".", 'c');
	int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0744);
	if (semid == -1) {
        	perror("semget");
    	}
    	union semun arg;
    	arg.val = 5;
    	int retval = semctl (semid, 0, SETVAL, arg);
    	
    	if(retval == 0) printf("Counting semaphore created successfully\n");
    	else perror("semctl");
}
	
