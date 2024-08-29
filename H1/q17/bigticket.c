/*
==================================================================================================================================================================================Name : handsonprog17.c
Author : bhanuja bhatt
Description : Write a program to simulate online ticket reservation. Implement write lock Write a program to open a file, store a ticket number and exit. 
	      Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.
Date: 25th Aug, 2024:
==================================================================================================================================================================================
==================================================================================================================================================================================
Sample Output: 
Before entering into critical section..
Inside the critical section...
Current ticket number: 16
Press enter to unlock and exit
Completed!

==================================================================================================================================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	struct flock fm;
	int ticketno;
	int fq = open("ticket.txt", O_RDWR);
	if(fq== -1){
		printf("Error: Could no open file\n");
	}
	else{
		read(fq, &ticketno, sizeof(ticketno));
		fm.l_type = F_WRLCK;
		fm.l_whence = SEEK_SET;
		fm.l_start = 0;
		fm.l_len = 0;
		fm.l_pid = getpid();
		printf("Before entering into critical section..\n");
		fcntl(fq, F_SETLKW, &fm);
		printf("Inside the critical section...\n");
		ticketno++;
		printf("Current ticket number: %d\n", ticketno);
		lseek(fq, 0, SEEK_SET);
		write(fq, &ticketno, sizeof(ticketno));
		printf("Press enter to unlock and exit");
		getchar();
		fm.l_type = F_UNLCK;
		fcntl(fq, F_SETLK, &fm);
		close(fq);
		printf("Completed!\n");
	}
	return 0;
}
