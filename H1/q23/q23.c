/*
======================================================================================================================================================================
Name : handsonprog23.c
Author : Bhanuja Bhatt
Description : Write a program to create a Zombie state of the running program
Date:21st aug, 2024
                                                                                      
======================================================================================================================================================================
*/
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main () {
	int child_pid;
	child_pid = fork();
	if (child_pid > 0) {
		sleep (20);
	}
	else {
		exit (0);
	}
	return 0;
}
