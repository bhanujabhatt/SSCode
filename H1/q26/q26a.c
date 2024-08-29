/*
==================================================================================================
Name : handsonprog26.c
Author : Bhanuja Bhatt
Description : Write a program to execute an executable program.
a. use some executable program
b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 27 Aug, 2024
===================================================================================================

===================================================================================================
Sample output:program executed successfully
===================================================================================================
*/#include <stdio.h>
#include <stdlib.h>

int main() {
    // Path to the executable
    char *executable_path = "./a.out > /dev/null 2>&1";

    // Execute the program without any arguments
    int status = system(executable_path);

    if (status == -1) {
        printf("Error executing the program.\n");
    } else {
        printf("Program executed successfully.\n");
    }

    return 0;
}

