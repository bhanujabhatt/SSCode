
/*
======================================================================================================================================================================
Name : q18.c
Author : BHANUJA BHATT
Description : Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.

Date: 17th sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:0

======================================================================================================================================================================
*/
#include<sys/types.h> 
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>

int main(){
	int fd1 [2], fd2 [2];
	pipe (fd1); 
	pipe (fd2);
	if (!fork()) {
		dup2 (fd1[1],1);

		close (fd1[0]); //closing read end of pipe

		close (fd2[0]);

		close (fd2[1]);

		execlp("ls", "ls", "-Rl", (char *) NULL);
	} 
	else {
		if(!fork()) {
		dup2 (fd1 [0],0); //read end of first pipe 
		
		dup2 (fd2 [1],1);//duplicated the write end of 2nd pipe 
		
		close (fd1 [1]);//closing the write end; 
		
		close (fd2 [0]);//closing read end of 2nd pipe 
		
		execlp ("grep", "grep", "^d", (char *) NULL);

		} 
		else {

			dup2 (fd2 [0],0); 
			
			close (fd2 [1]);

			close (fd1 [0]);

			close (fd1 [1]); 
			
			execlp("wc", "wc", "-l", (char *) NULL);
		}
	}
}
