#ifndef MANAGER_OPERATIONS_H
#define MANAGER_OPERATIONS_H

#include <stdbool.h>

// Function prototypes for manager operations
void Manager_operation_handler(int connFD);
void change_password_handler(int connFD, const char *fileName);
void activate_deactivate_customer(int connFD);
void assign_loan_applications(int connFD);
void review_customer_feedback(int connFD);
void logout_handler(int connFD);
void exit_handler(int connFD);
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "banking_system.h"  

// Manager Operation Handler
void Manager_operation_handler(int connFD) {
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes, writeBytes;
    bool isLoggedIn = false;

    // Login system for manager
    isLoggedIn = login_handler(true, connFD, NULL);  // Assuming `true` indicates a manager login
    if (!isLoggedIn) {
        return;  // If login fails, exit the function
    }

    while (1) {
        // Display menu options for the manager
        sprintf(writeBuffer, "Manager Operations:\n1. Activate/Deactivate Customer Accounts\n2. Assign Loan Applications\n3. Review Customer Feedback\n4. Change Password\n5. Logout\n6. Exit\nEnter your choice: ");
        writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
        if (writeBytes == -1) {
            perror("Error writing Manager operations menu to client!");
            return;
        }

        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        if (readBytes == -1) {
            perror("Error reading option from client!");
            return;
        }

        int choice = atoi(readBuffer);  // Convert the option to an integer

        switch (choice) {
            case 1:
                activate_deactivate_customer(connFD);  // Handle customer account activation/deactivation
                break;

            case 2:
                assign_loan_applications(connFD);  // Assign loan applications to employees
                break;

            case 3:
                review_customer_feedback(connFD);  // Review customer feedback
                break;

            case 4:
                change_password_handler(connFD, MANAGER_FILE);  // Change password
                break;

            case 5:
                logout_handler(connFD);  // Handle logout
                return;  // Exit the function after logout

            case 6:
                exit_handler(connFD);  // Exit the session
                return;  // End the manager session

            default:
                sprintf(writeBuffer, "Invalid choice! Please try again.\n");
                write(connFD, writeBuffer, strlen(writeBuffer));
                break;
        }
    }
}

void activate_deactivate_customer(int connFD) {
    char readBuffer[1000], writeBuffer[1000];
    int customerID;
    
    // Ask for customer ID to activate/deactivate
    sprintf(writeBuffer, "Enter Customer ID to Activate/Deactivate: ");
    write(connFD, writeBuffer, strlen(writeBuffer));
    read(connFD, readBuffer, sizeof(readBuffer));
    customerID = atoi(readBuffer);  // Convert to integer
    
    // Open customer file
    int customerFileFD = open(CUSTOMER_FILE, O_RDWR);
    if (customerFileFD == -1) {
        perror("Error opening customer file!");
        return;
    }

    // Lock the record, seek to customer position, read record, and modify status
    struct Customer customer;
    off_t offset = lseek(customerFileFD, customerID * sizeof(struct Customer), SEEK_SET);
    if (offset >= 0) {
        struct flock lock = {F_WRLCK, SEEK_SET, customerID * sizeof(struct Customer), sizeof(struct Customer), getpid()};
        fcntl(customerFileFD, F_SETLKW, &lock);

        read(customerFileFD, &customer, sizeof(struct Customer));
        customer.isActive = !customer.isActive;  // Toggle active status
        lseek(customerFileFD, -sizeof(struct Customer), SEEK_CUR);
        write(customerFileFD, &customer, sizeof(struct Customer));
        
        lock.l_type = F_UNLCK;
        fcntl(customerFileFD, F_SETLK, &lock);
    }

    close(customerFileFD);

    sprintf(writeBuffer, "Customer %d account is now %s.\n", customerID, customer.isActive ? "Activated" : "Deactivated");
    write(connFD, writeBuffer, strlen(writeBuffer));
}
void assign_loan_applications(int connFD) {
    char readBuffer[1000], writeBuffer[1000];
    int loanID, employeeID;

    // Ask for loan ID and employee ID to assign
    sprintf(writeBuffer, "Enter Loan ID to Assign: ");
    write(connFD, writeBuffer, strlen(writeBuffer));
    read(connFD, readBuffer, sizeof(readBuffer));
    loanID = atoi(readBuffer);

    sprintf(writeBuffer, "Enter Employee ID to assign Loan: ");
    write(connFD, writeBuffer, strlen(writeBuffer));
    read(connFD, readBuffer, sizeof(readBuffer));
    employeeID = atoi(readBuffer);

    // Open loan file, find the loan, and assign employee
    int loanFileFD = open(LOAN_FILE, O_RDWR);
    if (loanFileFD == -1) {
        perror("Error opening loan file!");
        return;
    }

    // Lock the loan record and assign employee
    struct Loan loan;
    off_t offset = lseek(loanFileFD, loanID * sizeof(struct Loan), SEEK_SET);
    if (offset >= 0) {
        struct flock lock = {F_WRLCK, SEEK_SET, loanID * sizeof(struct Loan), sizeof(struct Loan), getpid()};
        fcntl(loanFileFD, F_SETLKW, &lock);

        read(loanFileFD, &loan, sizeof(struct Loan));
        loan.assignedEmployeeID = employeeID;  // Assign employee ID
        lseek(loanFileFD, -sizeof(struct Loan), SEEK_CUR);
        write(loanFileFD, &loan, sizeof(struct Loan));
        
        lock.l_type = F_UNLCK;
        fcntl(loanFileFD, F_SETLK, &lock);
    }

    close(loanFileFD);

    sprintf(writeBuffer, "Loan %d assigned to Employee %d.\n", loanID, employeeID);
    write(connFD, writeBuffer, strlen(writeBuffer));
}
void review_customer_feedback(int connFD) {
    char writeBuffer[1000];
    
    // Open feedback file and read customer feedback
    int feedbackFileFD = open(FEEDBACK_FILE, O_RDONLY);
    if (feedbackFileFD == -1) {
        perror("Error opening feedback file!");
        return;
    }

    // Read feedback and send it to the manager
    while (read(feedbackFileFD, writeBuffer, sizeof(writeBuffer)) > 0) {
        write(connFD, writeBuffer, strlen(writeBuffer));
    }

    close(feedbackFileFD);
}
void change_password_handler(int connFD, const char* managerFile) {
    char readBuffer[1000], writeBuffer[1000], hashedPassword[1000];
    
    // Prompt for current password
    sprintf(writeBuffer, "Enter Current Password: ");
    write(connFD, writeBuffer, strlen(writeBuffer));
    read(connFD, readBuffer, sizeof(readBuffer));

    // Verify current password and prompt for a new one
    if (strcmp(crypt(readBuffer, SALT_BAE), manager.password) == 0) {
        sprintf(writeBuffer, "Enter New Password: ");
        write(connFD, writeBuffer, strlen(writeBuffer));
        read(connFD, readBuffer, sizeof(readBuffer));
        
        // Hash new password and update manager file
        strcpy(hashedPassword, crypt(readBuffer, SALT_BAE));
        update_manager_password(connFD, hashedPassword);
    } else {
        sprintf(writeBuffer, "Incorrect Current Password.\n");
        write(connFD, writeBuffer, strlen(writeBuffer));
    }
}
void logout_handler(int connFD) {
    char writeBuffer[1000];
    sprintf(writeBuffer, "Logging out...\n");
    write(connFD, writeBuffer, strlen(writeBuffer));
}
void exit_handler(int connFD) {
    char writeBuffer[1000];
    sprintf(writeBuffer, "Exiting...\n");
    write(connFD, writeBuffer, strlen(writeBuffer));
    close(connFD);  // Close the connection to the client
}




#endif // MANAGER_OPERATIONS_H

