/*
======================================================================================================================================================================
Name : handsonprog22.c
Author : Bhanuja Bhatt
Description : Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. Check output of the file.
Date: 21 aug, 2024
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Line written to file by parent process
Line written to file by child process

======================================================================================================================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	int fd, pid;
	fd = open("q22.txt", O_WRONLY|O_CREAT, 0666);
	if(fd == -1){
		printf("Error: could not open file\n");
	}
	else{
		pid = fork();
		if(pid){
			char buf[] = " written to file by parent process\n";
			write(fd, buf, sizeof(buf));
			close(fd);
		}
		else{
			char buf[] = " written to file by child process\n";
			write(fd, buf, sizeof(buf));
			close(fd);
		}
	}
	return 0;
}
