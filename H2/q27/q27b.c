
/*
======================================================================================================================================================================
Name : q27b.c
Author : BHANUJA BHATT
Description : Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag
Date: 15 sept, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:Enter the message type to receive: 290
Message type: 290
 : Success
Message text: second message

======================================================================================================================================================================
*/#include <sys/msg.h> 

#include <sys/ipc.h>

#include <sys/types.h>

#include <string.h>

#include <stdio.h>
int main () {

	int msgid, size; 
	key_t key;

	struct msg {

		long int mtype; 
		char message [80];

	}mq;

	key = ftok("/home/bhanuja-bhatt/my-repo2/H2/q26/a.txt", 'a');	
	msgid = msgget(key, 0);

	printf ("Enter the message type to receive: "); 
	scanf("%ld", &mq.mtype); 
	msgrcv (msgid, &mq, sizeof (mq.message), mq.mtype, IPC_NOWAIT); 
	printf ("Message type: %ld\n", mq.mtype); 
	perror(" ");

	printf ("Message text: %s\n", mq.message);
}
