
/*
======================================================================================================================================================================
Name : q29.c
Author : BHANUJA BHATT
Description :Write a program to remove the message queue.
Date: 14 sept, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Message queue with id 2 is removed

======================================================================================================================================================================
*/#include <unistd.h> 

#include <stdio.h>

#include <sys/msg.h>

#include <sys/ipc.h>

#include <sys/types.h>

#include <sys/time.h> 

#include <time.h>

int main(){
	int key = ftok("/home/bhanuja-bhatt/my-repo2/H2/q26/a.txt", 'a');
	
	int msqid = msgget(key, 0);
	
	int rtrn = msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
	
	if(rtrn == 0){
		printf("Message queue with id %d is removed\n", msqid);
	}
	
}
	
