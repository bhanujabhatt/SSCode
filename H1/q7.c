#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/stat.h>

int main(int argc, char* argv[]){
	if(argc < 3){
		perror("Please enter the source file and destination file names");
	}
	else{
		char buffer[1000];
		int fd1 = open(argv[1], O_RDONLY);
		int fd2 = open(argv[2], O_WRONLY|O_CREAT, 0666);
		if(fd1 == -1 || fd2 == -1){
			printf("Could not open the source and destination file\n");
		}
		else{

			int i = read(fd1, buffer, sizeof(buffer));
			while(i > 0){
				write(fd2, buffer, i);
				i = read(fd1, buffer, sizeof(buffer));
			}	
			printf("File copied successfully\n");
			close(fd1);
			close(fd2);
		}
	}
	return 0;
}
