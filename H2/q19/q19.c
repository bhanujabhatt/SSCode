
/*
======================================================================================================================================================================
Name : q19.c
Author : BHANUJA BHATT
Description : Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
c. mknod system call
d. mkfifo library function
Date: 17th sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:FIFO file created successfully using library call
FIFO file created successfully using mknod system call

======================================================================================================================================================================
*/
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>

int main(int argc, char* argv[]){
	//Create a FIFO file using mkfifo library call
	if(mkfifo("myfifofile", S_IFIFO|S_IRWXU) == -1){
		perror("mkfifo");
	}
	else {
		printf("FIFO file created successfully using library call\n");
	}
	//Create a FIFO file using mknod system call
	if(mknod("myfifofile1", S_IFIFO, 0) == -1){
		perror("Failed to create named pipe");
	}
	else {
		printf("FIFO file created successfully using mknod system call\n");
	}
	return 0;
}
