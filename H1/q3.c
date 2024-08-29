/*
================================================================================================================
Name : handsonprog3.c
Author :bhanuja bhatt
Description : Write a program to create a file and print the file descriptor value. Use creat ( ) system call
Date: 17th Aug, 2024
================================================================================================================

================================================================================================================
Sample Output:
File descriptor of created file: 3
================================================================================================================
*/

#include <stdio.h>
#include <fcntl.h>  
#include <unistd.h>

int main() {
    
    const char *filename = "m.txt";
    mode_t mode = 0644; 
    
    int fd = creat(filename, mode);

    if (fd == -1) {
        perror("creat");
        return 1;
    }

    printf("File descriptor: %d\n", fd);

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
