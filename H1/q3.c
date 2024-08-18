#include <stdio.h>
#include <fcntl.h>  
#include <unistd.h>

int main() {
    
    const char *filename = "m.txt";
    mode_t mode = 0644; // File permissions
    
    int fd = creat(filename, mode);

    if (fd == -1) {
        perror("creat");
        return 1;
    }

    printf("File descriptor: %d\n", fd);

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
