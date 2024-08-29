/*
==================================================================================================
Name : handsonprog1.c
Author : bhanuja bhatt
Description : 1. Create the following types of a files using (i) shell command (ii) system call
		a. soft link (symlink system call)
		b. hard link (link system call)
		c. FIFO (mkfifo Library Function or mknod system call)
Date: 10th Aug, 2024.
===================================================================================================

===================================================================================================
Sample output:
Hard link file created successfully
Soft link file created successfully
FIFO file created successfully
===================================================================================================
*/
#include <stdio.h>
#include <unistd.h>

int main() {
    const char *target = "q111.c";
    const char *symlink_name = "q--1";

    if (symlink(target, symlink_name) == -1) {
        perror("symlink");
        return 1;
    }

    printf("Symbolic link created successfully\n");
    return 0;
}

