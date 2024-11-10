#ifndef ADMIN_OPERATIONS_H
#define ADMIN_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <crypt.h> // For password encryption
#include <sys/types.h>
#include <sys/stat.h>
#include "./function/common.h"
#define CUSTOMER_FILE "customers.dat"
#define EMPLOYEE_FILE "employees.dat"
#define SALT_BAE "$6$salt"

#define ADMIN_LOGIN_WELCOME "Welcome Admin!"
#define ADMIN_LOGIN_ID "admin"
#define ADMIN_PASSWORD "$6$adminpass"
#define CUSTOMER_LOGIN_WELCOME "Welcome Customer!"
#define CUSTOMER_LOGIN_ID_DOESNT_EXIST "Customer login ID doesn't exist!"
#define PASSWORD "Enter Password: "
#define INVALID_LOGIN "Invalid login!"
#define INVALID_PASSWORD "Invalid password!"


struct Employee {
    char name[100];
    int id;
    char login[100];
    char password[100];
};

// Function declarations
void admin_operation_handler(int connFD);
void add_new_bank_employee(int connFD);
void modify_customer_employee_details(int connFD);
void manage_user_roles(int connFD);
void change_admin_password(int connFD);
void logout_admin(int connFD);

// Helper function to encrypt passwords
char *encrypt_password(const char *password) {
    struct crypt_data data;
    data.initialized = 0;
    return crypt(password, SALT_BAE);
}

// Main function that handles admin operations
void admin_operation_handler(int connFD) {
    if (login_handler(ROLE_ADMIN, connFD, NULL)) {
        ssize_t writeBytes, readBytes;
        char readBuffer[1000], writeBuffer[1000];
        int choice;

        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, ADMIN_LOGIN_WELCOME);
        write(connFD, writeBuffer, strlen(writeBuffer));

        while (1) {
            bzero(readBuffer, sizeof(readBuffer));
            bzero(writeBuffer, sizeof(writeBuffer));

            // Admin menu
            strcpy(writeBuffer, "ADMIN MENU:\n");
            strcat(writeBuffer, "1. Add New Bank Employee\n");
            strcat(writeBuffer, "2. Modify Customer/Employee Details\n");
            strcat(writeBuffer, "3. Manage User Roles\n");
            strcat(writeBuffer, "4. Change Password\n");
            strcat(writeBuffer, "5. Logout\n");
            strcat(writeBuffer, "6. Exit\n");
            strcat(writeBuffer, "Enter your choice: ");

            writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
            if (writeBytes == -1) {
                perror("Error writing admin menu to client!");
                return;
            }

            readBytes = read(connFD, readBuffer, sizeof(readBuffer));
            if (readBytes == -1) {
                perror("Error reading admin choice from client!");
                return;
            }

            choice = atoi(readBuffer); // Convert client's input to an integer

            switch (choice) {
                case 1:
                    add_new_bank_employee(connFD);
                    break;
                case 2:
                    modify_customer_employee_details(connFD);
                    break;
                case 3:
                    manage_user_roles(connFD);
                    break;
                case 4:
                    change_admin_password(connFD);
                    break;
                case 5:
                    logout_admin(connFD);
                    return;
                case 6:
                    exit(0);
                default:
                    bzero(writeBuffer, sizeof(writeBuffer));
                    strcpy(writeBuffer, "Invalid choice. Please try again.\n");
                    write(connFD, writeBuffer, strlen(writeBuffer));
                    break;
            }
        }
    }
}

// Function to add a new bank employee
void add_new_bank_employee(int connFD) {
    ssize_t writeBytes, readBytes;
    char readBuffer[1000], writeBuffer[1000];
    struct Employee newEmployee;

    bzero(readBuffer, sizeof(readBuffer));
    bzero(writeBuffer, sizeof(writeBuffer));

    // Request employee details from admin
    strcpy(writeBuffer, "Enter new employee details:\n");

    // Read name
    strcat(writeBuffer, "Name: ");
    write(connFD, writeBuffer, strlen(writeBuffer));
    read(connFD, newEmployee.name, sizeof(newEmployee.name));

    // Read ID
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "ID: ");
    write(connFD, writeBuffer, strlen(writeBuffer));
    bzero(readBuffer, sizeof(readBuffer));
    read(connFD, readBuffer, sizeof(readBuffer));
    newEmployee.id = atoi(readBuffer);

    // Read Role
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Role: ");
    write(connFD, writeBuffer, strlen(writeBuffer));
   
    // Save the new employee to the employee file
    int employeeFileFD = open(EMPLOYEE_FILE, O_WRONLY | O_APPEND);
    if (employeeFileFD == -1) {
        perror("Error opening employee file");
        return;
    }

    writeBytes = write(employeeFileFD, &newEmployee, sizeof(struct Employee));
    if (writeBytes == -1) {
        perror("Error writing new employee to file");
    } else {
        strcpy(writeBuffer, "New employee added successfully!\n");
        write(connFD, writeBuffer, strlen(writeBuffer));
    }

    close(employeeFileFD);
}

// Function to modify customer or employee details
void modify_customer_employee_details(int connFD) {
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];
    int userType, ID;
    struct Customer customer;
    struct Employee employee;

    bzero(readBuffer, sizeof(readBuffer));
    bzero(writeBuffer, sizeof(writeBuffer));

    // Ask admin to choose between customer or employee
    strcpy(writeBuffer, "Modify Details:\n1. Customer\n2. Employee\nEnter your choice: ");
    write(connFD, writeBuffer, strlen(writeBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    userType = atoi(readBuffer); // Convert the input to integer

    // Ask for the ID of the customer or employee
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter the ID: ");
    write(connFD, writeBuffer, strlen(writeBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    ID = atoi(readBuffer); // Convert the input to an integer

    if (userType == 1) {
        // Modify customer details
        int customerFileFD = open(CUSTOMER_FILE, O_RDWR);
        if (customerFileFD == -1) {
            perror("Error opening customer file");
            return;
        }

        off_t offset = lseek(customerFileFD, ID * sizeof(struct Customer), SEEK_SET);
        if (offset == -1) {
            perror("Error seeking to customer record");
            close(customerFileFD);
            return;
        }

        struct flock lock = {F_WRLCK, SEEK_SET, ID * sizeof(struct Customer), sizeof(struct Customer), getpid()};
        if (fcntl(customerFileFD, F_SETLKW, &lock) == -1) {
            perror("Error obtaining write lock on customer record");
            close(customerFileFD);
            return;
        }

        readBytes = read(customerFileFD, &customer, sizeof(struct Customer));
        if (readBytes == -1) {
            perror("Error reading customer record");
            close(customerFileFD);
            return;
        }

        // Show current details
        bzero(writeBuffer, sizeof(writeBuffer));
     write(connFD, writeBuffer, strlen(writeBuffer));

        // Modify details
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "Enter new name (or press Enter to skip): ");
        write(connFD, writeBuffer, strlen(writeBuffer));
        bzero(readBuffer, sizeof(readBuffer));
        read(connFD, readBuffer, sizeof(readBuffer));
        if (strlen(readBuffer) > 1)
            strcpy(customer.name, readBuffer);

        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "Enter new balance (or press Enter to skip): ");
        write(connFD, writeBuffer, strlen(writeBuffer));
        bzero(readBuffer, sizeof(readBuffer));
        read(connFD, readBuffer, sizeof(readBuffer));
        
        lseek(customerFileFD, ID * sizeof(struct Customer), SEEK_SET);
        writeBytes = write(customerFileFD, &customer, sizeof(struct Customer));
        if (writeBytes == -1) {
            perror("Error writing updated customer record");
        }

        lock.l_type = F_UNLCK;
        fcntl(customerFileFD, F_SETLK, &lock);
        close(customerFileFD);
    } else if (userType == 2) {
        // Modify employee details
        int employeeFileFD = open(EMPLOYEE_FILE, O_RDWR);
        if (employeeFileFD == -1) {
            perror("Error opening employee file");
            return;
        }

        off_t offset = lseek(employeeFileFD, ID * sizeof(struct Employee), SEEK_SET);
        if (offset == -1) {
            perror("Error seeking to employee record");
            close(employeeFileFD);
            return;
        }

        struct flock lock = {F_WRLCK, SEEK_SET, ID * sizeof(struct Employee), sizeof(struct Employee), getpid()};
        if (fcntl(employeeFileFD, F_SETLKW, &lock) == -1) {
            perror("Error obtaining write lock on employee record");
            close(employeeFileFD);
            return;
        }

        readBytes = read(employeeFileFD, &employee, sizeof(struct Employee));
        if (readBytes == -1) {
            perror("Error reading employee record");
            close(employeeFileFD);
            return;
        }

        // Show current details
        bzero(writeBuffer, sizeof(writeBuffer));
        sprintf(writeBuffer, "Current Details:\nName: %s\nID: %d\nRole: %s\n", employee.name, employee.id);
        write(connFD, writeBuffer, strlen(writeBuffer));

        // Modify details
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "Enter new name (or press Enter to skip): ");
        write(connFD, writeBuffer, strlen(writeBuffer));
        bzero(readBuffer, sizeof(readBuffer));
        read(connFD, readBuffer, sizeof(readBuffer));
        if (strlen(readBuffer) > 1)
            strcpy(employee.name, readBuffer);

        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "Enter new role (or press Enter to skip): ");
        write(connFD, writeBuffer, strlen(writeBuffer));
        bzero(readBuffer, sizeof(readBuffer));
        read(connFD, readBuffer, sizeof(readBuffer));
        lseek(employeeFileFD, ID * sizeof(struct Employee), SEEK_SET);
        writeBytes = write(employeeFileFD, &employee, sizeof(struct Employee));
        if (writeBytes == -1) {
            perror("Error writing updated employee record");
        }

        lock.l_type = F_UNLCK;
        fcntl(employeeFileFD, F_SETLK, &lock);
        close(employeeFileFD);
    } else {
        strcpy(writeBuffer, "Invalid choice!\n");
        write(connFD, writeBuffer, strlen(writeBuffer));
    }
}

// Function to change admin password
void change_admin_password(int connFD) {
    ssize_t writeBytes, readBytes;
    char readBuffer[1000], writeBuffer[1000], oldPassword[100], newPassword[100];
    struct crypt_data data;
    data.initialized = 0;

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter old password: ");
    write(connFD, writeBuffer, strlen(writeBuffer));

    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    strcpy(oldPassword, readBuffer);

    // Verify the old password
    if (strcmp(crypt(oldPassword, SALT_BAE), ADMIN_PASSWORD) != 0) {
        strcpy(writeBuffer, "Old password incorrect!\n");
        write(connFD, writeBuffer, strlen(writeBuffer));
        return;
    }

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter new password: ");
    write(connFD, writeBuffer, strlen(writeBuffer));

    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    strcpy(newPassword, readBuffer);

    // Encrypt the new password and save it
    strcpy(ADMIN_PASSWORD, crypt(newPassword, SALT_BAE));

    strcpy(writeBuffer, "Password changed successfully!\n");
    write(connFD, writeBuffer, strlen(writeBuffer));
}

// Function to log out admin
void logout_admin(int connFD) {
    ssize_t writeBytes;
    char writeBuffer[1000];

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Admin logged out successfully!\n");
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    if (writeBytes == -1) {
        perror("Error writing logout message to client!");
    }
}

#endif

