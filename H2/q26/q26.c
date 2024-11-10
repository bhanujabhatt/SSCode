/*
======================================================================================================================================================================
Name : q26.c
Author : BHANUJA BHATT
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 14 sept, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:Enter the message type: 102
Enter the message text: first message
bhanuja-bhatt@bhanuja-bhatt-HP-Laptop:~/my-repo2/H2/q26$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x611529b3 0          bhanuja-bh 744        0            0           
0x6115f54b 1          bhanuja-bh 744        0            0           
0x6115f642 2          bhanuja-bh 744        14           1           



======================================================================================================================================================================
*/
#include <sys/msg.h> 

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
	
	msgid = msgget(key, IPC_CREAT|0744);
	printf ("Enter the message type: "); 
	
	scanf("%ld", &mq.mtype);
	
	getchar();
	
	printf ("Enter the message text: "); 
	
	scanf("%[^\n]", mq.message); 
	
	size = strlen (mq.message);

	msgsnd (msgid, &mq, size+1, 0);
}
