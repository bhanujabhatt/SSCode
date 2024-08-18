#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char *filename = "c.txt";

    int fd = open(filename, O_CREAT | O_EXCL | O_RDWR, 0644); 

    if (fd == -1) {
        if (errno == EEXIST) {
            printf("File already exists.\n");
        } else {
            perror("open");
        }
        return 1;
    }

    printf("File created successfully with file descriptor: %d\n", fd);
    close(fd);

    return 0;
}
