#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    // Check if enough arguments are provided
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fifo_name>\n", argv[0]);
        return 1;
    }

    // Create the named pipe (FIFO)
    if (mknod(argv[1], S_IFIFO | 0666, 0) == -1) {
        perror("Failed to create named pipe");
        return 1;
    } else {
        printf("FIFO file '%s' created successfully\n", argv[1]);
    }

    return 0;
}
