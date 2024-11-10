
/*
======================================================================================================================================================================
Name : q2.c
Author : BHANUJA BHATT
Description : Write a program to print the system resource limits. Use getrlimit system call.
Date: 9 sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
CPU time limit (seconds):
  Soft limit: 18446744073709551615
  Hard limit: 18446744073709551615
Maximum file size (bytes):
  Soft limit: 18446744073709551615
  Hard limit: 18446744073709551615
Maximum data size (bytes):
  Soft limit: 18446744073709551615
  Hard limit: 18446744073709551615
Maximum stack size (bytes):
  Soft limit: 8388608
  Hard limit: 18446744073709551615
  Note: Soft limit is less than hard limit.
Maximum number of open files:
  Soft limit: 1024
  Hard limit: 1048576
  Note: Soft limit is less than hard limit.
Maximum address space (bytes):
  Soft limit: 18446744073709551615
  Hard limit: 18446744073709551615


======================================================================================================================================================================#include <stdio.h>
*/
#include <stdio.h>
#include <sys/resource.h>
#include <errno.h>
#include <string.h>

void print_limit(int resource, const char* resource_name) {
    struct rlimit rl;
    
    if (getrlimit(resource, &rl) == 0) {
        printf("%s:\n", resource_name);
        printf("  Soft limit: %lu\n", (unsigned long)rl.rlim_cur);
        printf("  Hard limit: %lu\n", (unsigned long)rl.rlim_max);
        if (rl.rlim_cur < rl.rlim_max) {
            printf("  Note: Soft limit is less than hard limit.\n");
        }
    } else {
        printf("Error retrieving %s limit: %s\n", resource_name, strerror(errno));
    }
}

int main() {
    print_limit(RLIMIT_CPU, "CPU time limit (seconds)");
    print_limit(RLIMIT_FSIZE, "Maximum file size (bytes)");
    print_limit(RLIMIT_DATA, "Maximum data size (bytes)");
    print_limit(RLIMIT_STACK, "Maximum stack size (bytes)");
    print_limit(RLIMIT_NOFILE, "Maximum number of open files");
    print_limit(RLIMIT_AS, "Maximum address space (bytes)");

    return 0;
}
