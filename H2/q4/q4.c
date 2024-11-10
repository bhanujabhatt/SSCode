
/*
======================================================================================================================================================================
Name : q4.c
Author : BHANUJA BHATT
Description : . Write a program to measure how much time is taken to execute 100 getppid ( )
system call. Use time stamp counter.
Date=9 sep,2024
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Time taken for 100 getppid() system calls: 79177 CPU cycles

======================================================================================================================================================================#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

static inline unsigned long long rdtsc(void) {
    unsigned int lo, hi;

    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((unsigned long long)hi << 32) | lo;
}

int main() {
    unsigned long long start_tsc, end_tsc;
    int i;

    start_tsc = rdtsc();

    for (i = 0; i < 100; i++) {
        getppid();
    }

    end_tsc = rdtsc();

    unsigned long long total_cycles = end_tsc - start_tsc;

    // Print the result
    printf("Time taken for 100 getppid() system calls: %llu CPU cycles\n", total_cycles);

    return 0;
}
