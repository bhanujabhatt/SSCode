/*
======================================================================================================================================================================
Name : q30d.c
Author : BHANUJA BHATT
Description : Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
Date: 14 sept, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Memory removed successfully


======================================================================================================================================================================
*/
#include <unistd.h> 

#include <stdio.h>

#include <sys/shm.h>

#include <sys/ipc.h>

#include <sys/types.h>

#include <sys/time.h> 

#include <time.h>

int main(){
	int key = ftok(".", 'b');
	const void *add;
	
	int shmid = shmget(key, 1024, 0);
	
	int retval = shmctl(shmid, IPC_RMID, NULL);
	if(retval == 0){
		printf("Memory removed successfully\n");
	}
	else{
		perror("shmctl");
	}
	
}
	
