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

