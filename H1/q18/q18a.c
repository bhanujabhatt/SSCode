/*
======================================================================================================================================================================
Name : handsonprog18.c
Author : Bhanuja Bhatt
Description : Write a program to perform Record locking.
		a. Implement write lock
		b. Implement read lock
		Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.
Date: 25th Aug, 2024
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Enter the record number: 
32
Before locking the record for writing
Write lock acquired successfully....
Enter roll number and marks:
12 52
Record written successfully!
Enter to unlock...

Finish

======================================================================================================================================================================
*/#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>

int main(){
	int x, fd;
	struct {
		int rollno;
		int marks;
	} mb;
	struct flock fq;
    fd = open("record.txt", O_WRONLY);
    
    printf("Enter the record number: \n");
    scanf("%d", &x);
    fq.l_type = F_WRLCK;
    fq.l_whence = SEEK_SET;
    fq.l_start = (x-1)*sizeof(mb);
    fq.l_len = sizeof(mb);
    fq.l_pid = getpid();
    printf("Before locking the record for writing\n");
    fcntl(fd, F_SETLKW, &fq);
    printf("Write lock acquired successfully....\n");
    printf("Enter roll number and marks:\n");
    scanf("%d", &mb.rollno);
    scanf("%d", &mb.marks);
    lseek(fd, (x-1)*sizeof(mb), SEEK_SET);
    write(fd, &mb, sizeof(mb));
    printf("Record written successfully!\n");
    printf("Enter to unlock...\n");
    getchar();
    getchar();
    fq.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &fq);
    printf("Finish\n");
    return 0;
}
