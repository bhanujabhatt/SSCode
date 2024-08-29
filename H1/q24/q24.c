/*
======================================================================================================================================================================
Name : handsonprog24.c
Author : Bhanuja BHatt
Description : Write a program to create an orphan process
Date:21st aug, 2024.
======================================================================================================================================================================
Sample Output:
n parent process, with PID: 110107
Child PID is: 110108
In child, process, PID: 110108
Parent PID is: 110107
bhanuja-bhatt@bhanuja-bhatt-HP-Laptop:~/my-repo2/H1/q24$ In child, process, PID: 110108
Parent PID is: 1788


======================================================================================================================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
int main()
{
	int k;
	k = fork();
	if(k==0)
    	{
    		printf("In child, process, PID: %d\n",getpid());
		printf("Parent PID is: %d\n",getppid());
		sleep(2); 
		printf("In child, process, PID: %d\n",getpid());
		printf("Parent PID is: %d\n",getppid());
    	}
	else
	{
		printf("In parent process, with PID: %d\n",getpid());
		printf("Child PID is: %d\n",k);
		exit(0);
	}
	return 0;
 }
