/*
======================================================================================================================================================================
Name : q21.c
Author : BHANUJA BHATT
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 14 sept, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
he text from FIFO: 
Enter the text: hhh



======================================================================================================================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main () { 
	char buf[80], buf1[80];

	int fd1, fd2;

	fd1 = open("myfifo1", O_RDONLY); 
	fd2 = open("myfifo2", O_WRONLY); 
	read (fd1, buf, sizeof (buf)); 
	printf ("The text from FIFO: %s\n", buf);
	
	printf ("Enter the text: "); 	
	scanf("%[^\n]", buf1); 		
	write (fd2, buf1, sizeof (buf1));			
	close(fd1);
	close(fd2);
	
}
