/*
======================================================================================================================================================================
Name : q20.c
Author : BHANUJA BHATT
Description :Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 14 sept, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
sample output
The text from FIFO: mynameisbhanuja

======================================================================================================================================================================
*/
#include <stdio.h> 
#include <unistd.h>
#include <fcntl.h>

int main () { 
	int fd; 
	char buf[80];

	fd = open("myfifo", O_RDONLY); 
	read (fd, buf, sizeof (buf)); 
	printf ("The text from FIFO: %s\n", buf);
}
