/*
======================================================================================================================================================================
Name : handsonprog8.c
Author : Bhanuja Bhatt
Description : Write a program to open a file in read only mode, read line by line and display each line as it is read. Close the file when end of file is reached.
Date: 18th Aug, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Hello, how are youbcb
This is written by the duplicate file descriptor
Using dup2
This is written by the original file descriptor
This is written by the duplicate file descriptor
Using fcntl
This is written by the original file descriptor
This is written by the duplicate file descriptor
This is written by the original file descriptor
This is written by the duplicate file descriptor
Using dup2
This is written by the original file descriptor
This is written by the duplicate file descriptor
Using fcntl
This is written by the original file descriptor
This is written by the duplicate file descriptor
This is written by the original file descriptor
This is written by the duplicate file descriptor
Using dup2
This is written by the original file descriptor
This is written by the duplicate file descriptor
Using fcntl
This is written by the original file descriptor
This is written by the duplicate file descriptor
======================================================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "a.txt"; 
    char line[256];  

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
   }
    fclose(file);

    return EXIT_SUCCESS;
}
