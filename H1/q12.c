#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char* argv[]){
	int fd1 = open(argv[1], O_RDWR);
	int currentflag = fcntl(fd1, F_GETFL);
	int om = currentflag & O_ACCMODE;
	if(om == O_RDONLY){
		printf("The file %s is opened only for reading\n", argv[1]);
	}
	else if(om  == O_WRONLY){
	       	printf("The file %s is opened only for writing\n", argv[1]);
	}
	else{
		printf("The file %s is opened for both reading and writing\n", argv[1]);
	}
	return 0;
}	
