#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *filename = "n.txt";
    int fd;
    ssize_t bytes_written;
    off_t offset;

    // Open the file in read-write mode, create it if it doesn't exist
    fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write 10 bytes to the file
    const char *data1 = "1234567890";
    bytes_written = write(fd, data1, 10);
    if (bytes_written != 10) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Move the file pointer by 10 bytes
    offset = lseek(fd, 10, SEEK_CUR);
    if (offset == (off_t) -1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Write another 10 bytes to the file
    const char *data2 = "abcdefghij";
    bytes_written = write(fd, data2, 10);
    if (bytes_written != 10) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Close the file
    close(fd);

    printf("File operations completed successfully.\n");
    return 0;
}

