#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define NUM_FILES 5
#define FILE_PREFIX "q"
#define FILE_SUFFIX ".txt"

int main() {
    int i;
    char filename[50];
    int filedescriptors[NUM_FILES];
    for (i = 0; i < NUM_FILES; ++i) {
        snprintf(filename, sizeof(filename), "%s%d%s", FILE_PREFIX, i, FILE_SUFFIX);
        filedescriptors[i] = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
        if (filedescriptors[i] < 0) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        printf("Created and opened file: %s\n", filename);
    }

    
    while (1) {
        sleep(1); 
    }

    for (i = 0; i < NUM_FILES; ++i) {
        close(filedescriptors[i]);
    }

    return 0;
}

