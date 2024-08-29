#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *args[] = {"ls", "-Rl", NULL};
    execvp("ls", args);
    perror("execvp"); // This will only be executed if execvp fails
    return EXIT_FAILURE;
}


