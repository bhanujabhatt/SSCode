#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct User {
    int id;
    char name[50];
    char login[50];
    char password[50];
};

void create_manager_file() {
    int fd = open("manager.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct User manager;

    // Example data
    manager.id = 1;
    strcpy(manager.name, "Alice Manager");
    strcpy(manager.login, "manager-1");
    strcpy(manager.password, "password123");  // In real-world use, store a hashed password

    // Write manager data to file
    ssize_t writtenBytes = write(fd, &manager, sizeof(manager));
    if (writtenBytes == -1) {
        perror("Error writing to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Add more records as needed
    manager.id = 2;
    strcpy(manager.name, "Bob Manager");
    strcpy(manager.login, "manager-2");
    strcpy(manager.password, "password456");
    write(fd, &manager, sizeof(manager));

    close(fd);
    printf("Manager data successfully written to file.\n");
}

int main() {
    create_manager_file();
    return 0;
}

