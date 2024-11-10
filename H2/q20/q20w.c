
/*
======================================================================================================================================================================
Name : q20.c
Author : BHANUJA BHATT
Description :Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 14 sept, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
sample output
Enter the text: mynameisbhanuja


======================================================================================================================================================================
*/#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main () { 
	char buf[80];

	int fd;

	fd = open("myfifo", O_WRONLY); 
	
	printf ("Enter the text: "); 
	
	scanf("%[^\n]", buf); 
	
	write (fd, buf, sizeof (buf));
}
