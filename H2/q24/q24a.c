/*
======================================================================================================================================================================
Name : q24.c
Author : BHANUJA BHATT
Description : Write a program to create a message queue and print the key and message queue id.
system call with FIFO.
Date: 19 sept, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
The key is = 1628776883
The key is = 0x611529b3
The message queue id is = 1

======================================================================================================================================================================
*/#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h> // For exit()

int main() {
    // Generate IPC key
    key_t key = ftok("a.txt", 'A');
    
    // Check if ftok failed
    if (key == -1) {
        perror("ftok failed");
        exit(1); // Exit with error code
    }

    // Create a message queue with read/write permissions
    int msgid = msgget(key, IPC_CREAT | 0666);
    
    // Check if msgget failed
    if (msgid == -1) {
        perror("msgget failed");
        exit(1); // Exit with error code
    }

    // Print the key and message queue ID
    printf("Message queue key: %d\n", key);
    printf("Message queue ID: %d\n", msgid);

    return 0;
}

