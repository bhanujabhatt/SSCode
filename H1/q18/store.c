#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>

int main(){

	int i, fd; 
	struct {
		int rollno;
		int marks;
	} mb[3];

	for (i=0;i<3;i++){

		mb[i].rollno=i+1; 
		mb[i].marks=0;
	}
	fd = open ("record.txt", O_RDWR|O_CREAT, 0666); 
	write(fd, &mb, sizeof(mb)); 
	close(fd);
	return 0;
}
