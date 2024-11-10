
/*
======================================================================================================================================================================
Name : q5.c
Author : BHANUJA BHATT
Description : Write a program to print the system limitation of
a. maximum length of the arguments to the exec family of functions.
b. maximum number of simultaneous process per user id.
c. number of clock ticks (jiffy) per second.
d. maximum number of open files
e. size of a page
f. total number of pages in the physical memory
g. number of currently available pages in the physical memory.
Date: 10 sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
a. Maximum length of arguments to exec functions: 2097152 bytes
b. Maximum number of simultaneous processes per user id: 30980
c. Number of clock ticks per second: 100
d. Maximum number of open files: 1024
e. Size of a page: 4096 bytes
f. Total number of pages in physical memory: 2001480
g. Number of currently available pages in physical memory: 791636

======================================================================================================================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>

int main() {
    
    long arg_max = sysconf(_SC_ARG_MAX);
    if (arg_max != -1) {
        printf("a. Maximum length of arguments to exec functions: %ld bytes\n", arg_max);
    } else {
        perror("sysconf(_SC_ARG_MAX) failed");
    }

    long max_processes = sysconf(_SC_CHILD_MAX);
    if (max_processes != -1) {
        printf("b. Maximum number of simultaneous processes per user id: %ld\n", max_processes);
    } else {
        perror("sysconf(_SC_CHILD_MAX) failed");
    }

    long clock_ticks = sysconf(_SC_CLK_TCK);
    if (clock_ticks != -1) {
        printf("c. Number of clock ticks per second: %ld\n", clock_ticks);
    } else {
        perror("sysconf(_SC_CLK_TCK) failed");
    }

    long open_files = sysconf(_SC_OPEN_MAX);
    if (open_files != -1) {
        printf("d. Maximum number of open files: %ld\n", open_files);
    } else {
        perror("sysconf(_SC_OPEN_MAX) failed");
    }

    long page_size = sysconf(_SC_PAGESIZE);
    if (page_size != -1) {
        printf("e. Size of a page: %ld bytes\n", page_size);
    } else {
        perror("sysconf(_SC_PAGESIZE) failed");
    }

    long total_pages = sysconf(_SC_PHYS_PAGES);
    if (total_pages != -1) {
        printf("f. Total number of pages in physical memory: %ld\n", total_pages);
    } else {
        perror("sysconf(_SC_PHYS_PAGES) failed");
    }
    long avail_pages = sysconf(_SC_AVPHYS_PAGES);
    if (avail_pages != -1) {
        printf("g. Number of currently available pages in physical memory: %ld\n", avail_pages);
    } else {
        perror("sysconf(_SC_AVPHYS_PAGES) failed");
    }

    return 0;
}
