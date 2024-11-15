/*
======================================================================================================================================================================
Name : q17c.c
Author : BHANUJA BHATT
Description : Write a program to execute ls -l | wc.
a. use dup
b. use dup2
c. use fcntl
Date: 20th sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
 5      38     275

======================================================================================================================================================================
*/
#include <stdio.h> 
#include <unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main (void) { 
	int fd[2];

	pipe (fd);

	if(!fork()) {

		close (1);

		close (fd[0]);

		fcntl(fd[1], F_DUPFD, 1); 
		execlp ("ls", "ls", "-l", (char *) NULL); 
	}

	else { 
		close (0);

		close (fd[1]); 
		fcntl(fd[0], F_DUPFD, 0);

		execlp ("wc", "wc", (char *) NULL);

	}
}
