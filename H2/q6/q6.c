

/*
======================================================================================================================================================================
Name : q6.c
Author : BHANUJA BHATT
Description : Write a simple program to create three threads.
10micro second
a. ITIMER_REAL
b. ITIMER_VIRTUAL
c. ITIMER_PROF
Date: 11 sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Thread 1 is running
Thread 2 is running
Thread 3 is running
All threads have finished execution.

======================================================================================================================================================================
*/
#include <stdio.h>
#include <pthread.h>

// Function to be executed by each thread
void* thread_function(void* arg) {
    int thread_num = *((int*)arg);
    printf("Thread %d is running\n", thread_num);
    return NULL;
}

int main() {
    pthread_t threads[3]; // Array to hold thread IDs
    int thread_args[3];   // Arguments for each thread

    // Create three threads
    for (int i = 0; i < 3; i++) {
        thread_args[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished execution.\n");
    return 0;
} 
