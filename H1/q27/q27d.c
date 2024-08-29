#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *args[] = {"/bin/ls", "-Rl", NULL};
    execv("/bin/ls", args);
    perror("execv"); 
    return EXIT_FAILURE;
}

