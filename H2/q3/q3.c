
/*
======================================================================================================================================================================
Name : q3.c
Author : BHANUJA BHATT
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 9 sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Maximum number of open files (before setting new limit):
  Soft limit: 1024
  Hard limit: 1048576
Successfully set new file descriptor limits.
Maximum number of open files (after setting new limit):
  Soft limit: 1024
  Hard limit: 2048


======================================================================================================================================================================
*/
#include <stdio.h>
#include <sys/resource.h>
#include <errno.h>
#include <string.h>

void print_limit(int resource, const char* resource_name) {
    struct rlimit rl;
    
    if (getrlimit(resource, &rl) == 0) {
        printf("%s:\n", resource_name);
        printf("  Soft limit: %ld\n", (long)rl.rlim_cur);
        printf("  Hard limit: %ld\n", (long)rl.rlim_max);
    } else {
        printf("Error retrieving %s limit: %s\n", resource_name, strerror(errno));
    }
}

int main() {
    struct rlimit rl;

    print_limit(RLIMIT_NOFILE, "Maximum number of open files (before setting new limit)");

    rl.rlim_cur = 1024;  
    rl.rlim_max = 2048; 
    
    if (setrlimit(RLIMIT_NOFILE, &rl) == 0) {
        printf("Successfully set new file descriptor limits.\n");
    } else {
        printf("Error setting new limits: %s\n", strerror(errno));
        return 1;
    }

    print_limit(RLIMIT_NOFILE, "Maximum number of open files (after setting new limit)");

    return 0;
}
