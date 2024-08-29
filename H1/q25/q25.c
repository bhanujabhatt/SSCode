/*
======================================================================================================================================================================
Name : handsonprog25.c
Author : Bhanuja Bhatt
Description : Write a program to create three child processes. The parent should wait for a particular child (use waitpid system call).
Date: 22 aug, 2024.
======================================================================================================================================================================
======================================================================================================================================================================
Sample Output:
Child process 1 exiting
Child process 3 exiting

Child process 2 exited with status: 2
Parent process exiting

======================================================================================================================================================================

*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	int pid1,pid2,pid3, s;
	pid1 = fork();
	if(pid1 > 0){
		pid2 = fork();
		if(pid2 > 0){
			pid3 = fork();
			if(pid3 > 0){
				waitpid(pid2, &s, 0);
				printf("Child process 2 exited with status: %d\n",WEXITSTATUS(s));
			}
			else{
				printf("Child process 3 exiting\n");
				exit(0);
			}
		}
		else{
			sleep(3);
			exit(2);
		}
		printf("Parent process exiting\n");
	}
	else{
		printf("Child process 1 exiting\n");
		exit(0);
	}
	return 0;
}
