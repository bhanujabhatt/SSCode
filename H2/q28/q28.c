
/*
======================================================================================================================================================================
Name : q28.c
Author : BHANUJA BHATT
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 14 sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:The key is = 1628829250
The message queue id is = 2
Existing Permission: 744
New Permission: 655

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
	
	int qid = msgget(key, 0);
	
	struct ipc_perm msg_perm; 
	
	struct msqid_ds mq;
	
	struct msginfo info;

	printf("The key is = %d\n", key);
	
	printf("The message queue id is = %d\n", qid);
	
	msgctl (qid, IPC_STAT, &mq);

	printf ("Existing Permission: %03o\n", mq.msg_perm.mode & 0777);
	
	mq.msg_perm.mode = 0655;
	
	msgctl (qid, IPC_SET, &mq);
	
	printf ("New Permission: %03o\n", mq.msg_perm.mode & 0777);}
	
