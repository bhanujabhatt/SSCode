
/*
======================================================================================================================================================================
Name : q23.c
Author : BHANUJA BHATT
Description :  Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 19 sept, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Pipe_buf = 4096
Open max = 1024
======================================================================================================================================================================
*/
#include <stdio.h> 
#include <unistd.h>

int main () {

	long PIPE_BUF, OPEN_MAX;

	PIPE_BUF = pathconf(".", _PC_PIPE_BUF);

	OPEN_MAX= sysconf(_SC_OPEN_MAX);

	printf ("Pipe_buf = %ld\nOpen max = %ld\n", PIPE_BUF, OPEN_MAX);
}