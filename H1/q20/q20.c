#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char* argv[]){
	int pid = getpid();
	int priority = getpriority(PRIO_PROCESS, pid);
	printf("Current priority of process: %d\n", priority+30);
	if(argc < 2){
		printf("Error, please enter a value for priority\n");
	}
	else{
		printf("Nice value = %s\n", argv[1]);
		setpriority(PRIO_PROCESS, pid, atoi(argv[1]));
		priority = getpriority(PRIO_PROCESS, pid);
		printf("New priority of the process set to: %d\n", priority+30);
	}
	return 0;
}
