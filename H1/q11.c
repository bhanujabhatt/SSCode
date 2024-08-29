/*
=================================================================================================================================================================================
Name : handsonq11
Author : Bhanuja Bhatt
Description : Write a program to open a file, duplicate the file descriptor and append the file with both the descriptors and check whether the file is updated properly or not.
		a. use dup
		b. use dup2
		c. use fcntl
Date: 18th Aug, 2024
=================================================================================================================================================================================

=================================================================================================================================================================================
Sample Output:
Using dup
fd1 = 3
fd2 = 4
Duplication successful...
Using dup2
fd1 = 3
fd3 = 27
Duplication successful...
Using fcntl
fd1 = 3
fd4 = 28
Duplication successful...
=================================================================================================================================================================================
*/
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(){
	int fd	= open("a.txt", O_RDWR|O_APPEND);
	int x, y, z;
	if(fd == -1)
	{
		perror("open");
	}
	else{
		printf("Using dup\n");
		x = dup(fd);
		printf("fd1 = %d\n", fd);
		printf("x = %d\n", x);
		write(fd, "This is written by the original file descriptor\n", 48);
		write(x, "This is written by the duplicate file descriptor\n", 49);
		printf("Duplication successful...\n");
		printf("Using dup2\n");
		y = dup2(fd, 27);
		printf("fd1 = %d\n", fd);
		printf("y = %d\n", y);
		write(fd, "Using dup2\nThis is written by the original file descriptor\n", 59);
		write(x, "This is written by the duplicate file descriptor\n", 49);
		printf("Duplication successful...\n");
		printf("Using fcntl\n");
		z = fcntl(fd, F_DUPFD, 27);
		printf("fd1 = %d\n", fd);
		printf("z = %d\n", z);
		write(fd, "Using fcntl\nThis is written by the original file descriptor\n", 60);
		write(y, "This is written by the duplicate file descriptor\n", 49);
		printf("Duplication successful...\n");
		close(fd);
		close(x);
		close(y);
		close(z);
	}
	return 0;
}  
