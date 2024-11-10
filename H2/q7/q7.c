
/*
======================================================================================================================================================================
Name : q7.c
Author : BHANUJA BHATT
Description : Write a simple program to print the created thread ids. 
Date: 12 sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Thread ID: 140217386268352 is running
Thread ID: 140217377875648 is running
Thread ID: 140217369482944 is running
All threads have finished execution.

======================================================================================================================================================================
*/
#include <stdio.h>
#include <pthread.h>

// Function to be executed by each thread
void* thread_function(void* arg) {
    pthread_t thread_id = pthread_self(); // Get the thread ID of the current thread
    printf("Thread ID: %lu is running\n", thread_id); // Print the thread ID
    return NULL;
}

int main() {
    pthread_t threads[3]; // Array to hold thread IDs

    // Create three threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_function, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished execution.\n");
    return 0;
}

