/*Name : handsonprog6.c
Author : Bhanuja bhatt
Description : Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls
Date: 18th Aug, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Hello
Hello
Hi
Hi
Hello World
Hello World
======================================================================================================================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	char bufferr[300];
	int j;
	while(1){
		int j = read(0, bufferr, sizeof(bufferr));
		if(j>1)
			write(1, bufferr, j);
		else
			break;
	}

	return 0;
}
