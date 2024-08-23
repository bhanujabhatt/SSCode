#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>

int main(){
	int x, fd;
	struct {
		int rollno;
		int marks;
	} mb;
	struct flock fq;
    fd = open("record.txt", O_RDONLY);
    
    printf("Enter the record number: \n");
    scanf("%d", &x);
    fq.l_type = F_RDLCK;
    fq.l_whence = SEEK_SET;
    fq.l_start = (x-1)*sizeof(mb);
    fq.l_len = sizeof(mb);
    fq.l_pid = getpid();
    printf("Before locking the record for reading\n");
    fcntl(fd, F_SETLKW, &fq);
    printf("Read lock acquired successfully....\n");
    lseek(fd, (x-1)*sizeof(mb), SEEK_SET);
    read(fd, &mb, sizeof(mb));
    printf("The record details are:\n");
    printf("Roll No: %d\n", mb.rollno);
    printf("Marks: %d\n", mb.marks);
    printf("Enter to unlock...\n");
    getchar();
    getchar();
    fq.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &fq);
    printf("Finish\n");
    return 0;
}
