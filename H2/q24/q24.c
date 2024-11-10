
/*
======================================================================================================================================================================
Name : q24.c
Author : BHANUJA BHATT
Description : Write a program to create a message queue and print the key and message queue id.
system call with FIFO.
Date: 19 sept, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
The key is = 1628776883
The key is = 0x611529b3
The message queue id is = 0

======================================================================================================================================================================
*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

int main(){
	int key = ftok("/home/bhanuja-bhatt/my-repo2/H2/q24/a.txt", 'a');
	int qid = msgget(key, IPC_CREAT|0744);

	printf("The key is = %d\n", key);
	printf("The key is = 0x%0x\n", key);
	printf("The message queue id is = %d\n", qid);
}
