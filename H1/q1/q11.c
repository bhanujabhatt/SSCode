#include <stdio.h>
#include <unistd.h>

int main() {
    const char *target = "q111.c";
    const char *symlink_name = "q--1";

    if (symlink(target, symlink_name) == -1) {
        perror("symlink");
        return 1;
    }

    printf("Symbolic link created successfully\n");
    return 0;
}

