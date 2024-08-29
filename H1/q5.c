/*
======================================================================================================================================================================
Name : handsonprog5.c
Author : Bhanuja Bhatt
Description : Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.
Date: 10th Aug, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output :
pid=101769 
total 0
lrwx------ 1 bhanuja-bhatt bhanuja-bhatt 64 Aug 29 11:11 0 -> /dev/pts/0
lrwx------ 1 bhanuja-bhatt bhanuja-bhatt 64 Aug 29 11:11 1 -> /dev/pts/0
lrwx------ 1 bhanuja-bhatt bhanuja-bhatt 64 Aug 29 11:11 2 -> /dev/pts/0
lrwx------ 1 bhanuja-bhatt bhanuja-bhatt 64 Aug 29 11:11 3 -> /home/bhanuja-bhatt/my-repo2/H1/q0.txt
lrwx------ 1 bhanuja-bhatt bhanuja-bhatt 64 Aug 29 11:11 4 -> /home/bhanuja-bhatt/my-repo2/H1/q1.txt
lrwx------ 1 bhanuja-bhatt bhanuja-bhatt 64 Aug 29 11:11 5 -> /home/bhanuja-bhatt/my-repo2/H1/q2.txt
lrwx------ 1 bhanuja-bhatt bhanuja-bhatt 64 Aug 29 11:11 6 -> /home/bhanuja-bhatt/my-repo2/H1/q3.txt
lrwx------ 1 bhanuja-bhatt bhanuja-bhatt 64 Aug 29 11:11 7 -> /home/bhanuja-bhatt/my-repo2/H1/q4.txt

*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define NUM_FILES 5
#define FILE_PREFIX "q"
#define FILE_SUFFIX ".txt"

int main() {
    int i;
    char filename[50];
    int filedescriptors[NUM_FILES];
    for (i = 0; i < NUM_FILES; ++i) {
        snprintf(filename, sizeof(filename), "%s%d%s", FILE_PREFIX, i, FILE_SUFFIX);
        filedescriptors[i] = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
        if (filedescriptors[i] < 0) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        printf("Created and opened file: %s\n", filename);
    }

    
    while (1) {
        sleep(1); 
    }

    for (i = 0; i < NUM_FILES; ++i) {
        close(filedescriptors[i]);
    }

    return 0;
}

