#ifndef COMMON_FUNCTIONS
#define COMMON_FUNCTIONS
#define ROLE_ADMIN    4:
#define ROLE_MANAGER  3
#define ROLE_EMPLOYEE 2
#define ROLE_CUSTOMER 1


#include <stdio.h>     // Import for `printf` & `perror`
#include <unistd.h>    // Import for `read`, `write & `lseek`
#include <string.h>    // Import for string functions
#include <stdbool.h>   // Import for `bool` data type
#include <sys/types.h> // Import for `open`, `lseek`
#include <sys/stat.h>  // Import for `open`
#include <fcntl.h>     // Import for `open`
#include <stdlib.h>    // Import for `atoi`
#include <errno.h>     // Import for `errno`
typedef enum {
    ROLE_CUSTOMER,
    ROLE_EMPLOYEE,
    ROLE_MANAGER,
    ROLE_ADMIN
} UserRole;

bool login_handler(UserRole role, int connFD, void* userStruct)
bool read_credentials_from_file(const char* filePath, const char* username, const char* password)
// Function to apply file locking and read credentials from a file
bool read_credentials_from_file(const char* filePath, const char* username, const char* password) {
    // Open the file in read-only mode
    int fd = open(filePath, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return false;
    }

    // Apply a read lock on the file using fcntl
    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_RDLCK;   // Set a read lock
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;          // Lock the entire file

    // Try to apply the lock
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error applying file lock");
        close(fd);
        return false;
    }

    // Read the file for username and password
    FILE *file = fdopen(fd, "r");
    if (!file) {
        perror("Error opening file stream");
        close(fd);
        return false;
    }

    char fileUsername[100], filePassword[50];
    bool loginSuccess = false;
    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            loginSuccess = true;  // Successful login
            break;
        }
    }

    // Release the lock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Error releasing file lock");
    }

    // Close the file descriptor
    fclose(file);
    close(fd);

    return loginSuccess;
}

bool login_handler(UserRole role, int connFD, void* userStruct) {
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];

    // Send login prompt to client
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter your username and password:\n");
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    if (writeBytes == -1) {
        perror("Error while writing login prompt to client!");
        return false;
    }

    // Read the username and password from the client
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (readBytes == -1) {
        perror("Error while reading login credentials from client!");
        return false;
    }

    // Assuming the credentials are in the format "username password"
    char username[100], password[50];
    sscanf(readBuffer, "%s %s", username, password); // Parse the input

    // Validate credentials based on the user role
    switch (role) {
        case ROLE_CUSTOMER:
        {
            struct Customer* customer = (struct Customer*)userStruct;
            // Read customer credentials from a file (e.g., customers.txt)
            if (read_credentials_from_file("customers.txt", username, password)) {
                strcpy(customer->name, username);
                bzero(writeBuffer, sizeof(writeBuffer));
                strcpy(writeBuffer, "Customer Login Successful\n");
                write(connFD, writeBuffer, strlen(writeBuffer));
                return true;
            } else {
                bzero(writeBuffer, sizeof(writeBuffer));
                strcpy(writeBuffer, "Customer Login Failed. Invalid credentials.\n");
                write(connFD, writeBuffer, strlen(writeBuffer));
                return false;
            }
        }
        case ROLE_EMPLOYEE:
        {
            struct Employee* employee = (struct Employee*)userStruct;
            // Read employee credentials from a file (e.g., employees.txt)
            if (read_credentials_from_file("employees.txt", username, password)) {
                strcpy(employee->name, username);
                bzero(writeBuffer, sizeof(writeBuffer));
                strcpy(writeBuffer, "Employee Login Successful\n");
                write(connFD, writeBuffer, strlen(writeBuffer));
                return true;
            } else {
                bzero(writeBuffer, sizeof(writeBuffer));
                strcpy(writeBuffer, "Employee Login Failed. Invalid credentials.\n");
                write(connFD, writeBuffer, strlen(writeBuffer));
                return false;
            }
        }
        case ROLE_MANAGER:
        {
            struct Manager* manager = (struct Manager*)userStruct;
            // Read manager credentials from a file (e.g., managers.txt)
            if (read_credentials_from_file("managers.txt", username, password)) {
                strcpy(manager->name, username);
                bzero(writeBuffer, sizeof(writeBuffer));
                strcpy(writeBuffer, "Manager Login Successful\n");
                write(connFD, writeBuffer, strlen(writeBuffer));
                return true;
            } else {
                bzero(writeBuffer, sizeof(writeBuffer));
                strcpy(writeBuffer, "Manager Login Failed. Invalid credentials.\n");
                write(connFD, writeBuffer, strlen(writeBuffer));
                return false;
            }
        }
        case ROLE_ADMIN:
        {
            struct Admin* admin = (struct Admin*)userStruct;
            // Read admin credentials from a file (e.g., admins.txt)
            if (read_credentials_from_file("admins.txt", username, password)) {
                strcpy(admin->name, username);
                bzero(writeBuffer, sizeof(writeBuffer));
                strcpy(writeBuffer, "Admin Login Successful\n");
                write(connFD, writeBuffer, strlen(writeBuffer));
                return true;
            } else {
                bzero(writeBuffer, sizeof(writeBuffer));
                strcpy(writeBuffer, "Admin Login Failed. Invalid credentials.\n");
                write(connFD, writeBuffer, strlen(writeBuffer));
                return false;
            }
        }
        default:
            bzero(writeBuffer, sizeof(writeBuffer));
            strcpy(writeBuffer, "Invalid user role!\n");
            write(connFD, writeBuffer, strlen(writeBuffer));
            return false;
    }
}

