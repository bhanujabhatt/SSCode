
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
