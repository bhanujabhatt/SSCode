/*
======================================================================================================================================================================
Name : handsonprog27.c
Author : Bhanuja Bhatt
Description : Write a program to execute ls -Rl by the following system calls
a. execl
b. execlp
c. execled. execv
e. execvp
Date: 25aug, 2024
======================================================================================================================================================================
======================================================================================================================================================================
Sample Output:
total 36
-rwxrwxr-x 1 bhanuja-bhatt bhanuja-bhatt 16000 Aug 29 14:20 a.out
-rw-rw-r-- 1 bhanuja-bhatt bhanuja-bhatt  1159 Aug 29 14:19 q27a.c
-rw-rw-r-- 1 bhanuja-bhatt bhanuja-bhatt   160 Aug 28 23:01 q27b.c
-rw-rw-r-- 1 bhanuja-bhatt bhanuja-bhatt     0 Aug 28 18:33 q27.c
-rw-rw-r-- 1 bhanuja-bhatt bhanuja-bhatt   199 Aug 28 23:02 q27c.c
-rw-rw-r-- 1 bhanuja-bhatt bhanuja-bhatt   196 Aug 28 23:03 q27d.c
-rw-rw-r-- 1 bhanuja-bhatt bhanuja-bhatt   234 Aug 28 23:05 q27e.c

======================================================================================================================================================================

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    execlp("ls", "ls", "-Rl", NULL);
    perror("execlp"); 
    return EXIT_FAILURE;
}
