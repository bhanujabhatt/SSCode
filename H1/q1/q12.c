#include <unistd.h>
#include <stdio.h>

int main() {
    const char *original = "q122.c";
    const char *hardlink ="ql1 l";

    if (link(original, hardlink) != 0) {
        perror("link");
        return 1;
    }

    printf("Hard link created successfully.\n");
    return 0;
}

