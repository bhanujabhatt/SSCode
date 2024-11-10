#ifndef TRANSACTION_HISTORY_H
#define TRANSACTION_HISTORY_H

#include "banking_system.h"  // Include necessary structures

void view_transaction_history(int connFD, struct Customer *customer);

#endif // TRANSACTION_HISTORY_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <crypt.h>
#include "banking_system.h"  // Include the header file for necessary structures

// Function prototypes for different customer operations
void view_account_balance(int connFD, struct Customer *customer);
void deposit_money(int connFD, struct Customer *customer);
void withdraw_money(int connFD, struct Customer *customer);
void transfer_funds(int connFD, struct Customer *customer);
void apply_for_loan(int connFD, struct Customer *customer);
void change_customer_password(int connFD, struct Customer *customer);
void add_feedback(int connFD, struct Customer *customer);
void view_transaction_history(int connFD, struct Customer *customer);
void logout_customer(int connFD, struct Customer *customer);

// Main handler for customer operations
void customer_operation_handler(int connFD, struct Customer *customer) {
    ssize_t writeBytes, readBytes;
    char readBuffer[1000], writeBuffer[1000];

    while (1) {
        // Present the customer with the available options
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "\nCustomer Menu:\n"
                            "1. View Account Balance\n"
                            "2. Deposit Money\n"
                            "3. Withdraw Money\n"
                            "4. Transfer Funds\n"
                            "5. Apply for a Loan\n"
                            "6. Change Password\n"
                            "7. Add Feedback\n"
                            "8. View Transaction History\n"
                            "9. Logout\n"
                            "10. Exit\n"
                            "Enter your choice: ");
        write(connFD, writeBuffer, strlen(writeBuffer));

        // Read the customer's choice
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        int choice = atoi(readBuffer);

        // Handle the customer's choice
        switch (choice) {
            case 1:
                view_account_balance(connFD, customer);
                break;
            case 2:
                deposit_money(connFD, customer);
                break;
            case 3:
                withdraw_money(connFD, customer);
                break;
            case 4:
                transfer_funds(connFD, customer);
                break;
            case 5:
                apply_for_loan(connFD, customer);
                break;
            case 6:
                change_customer_password(connFD, customer);
                break;
            case 7:
                add_feedback(connFD, customer);
                break;
            case 8:
                view_transaction_history(connFD, customer);
                break;
            case 9:
                // Call the logout function
                logout_customer(connFD, customer);
                return; // Exit the customer session
            case 10:
                // Exit the system
                bzero(writeBuffer, sizeof(writeBuffer));
                strcpy(writeBuffer, "Thank you for using our service. Goodbye!\n");
                write(connFD, writeBuffer, strlen(writeBuffer));
                close(connFD);
                exit(0); // Terminate the process
            default:
                // Invalid choice
                bzero(writeBuffer, sizeof(writeBuffer));
                strcpy(writeBuffer, "Invalid choice. Please try again.\n");
                write(connFD, writeBuffer, strlen(writeBuffer));
                break;
        }
    }
}

// Function to handle customer logout
void logout_customer(int connFD, struct Customer *customer) {
    char writeBuffer[1000];

    // Perform any necessary cleanup operations here
    // For example, log the logout event, update session status, etc.

    // Inform the customer
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "You have been logged out successfully.\n");
    write(connFD, writeBuffer, strlen(writeBuffer));

    // Close the connection if necessary (depending on how your server handles connections)
    // close(connFD);
}

// Function to view account balance
void view_account_balance(int connFD, struct Customer *customer) {
    char writeBuffer[1000];
    bzero(writeBuffer, sizeof(writeBuffer));
    sprintf(writeBuffer, "Your current account balance is: %.2f\n", customer->accountBalance);
    write(connFD, writeBuffer, strlen(writeBuffer));
}

// Function to deposit money
void deposit_money(int connFD, struct Customer *customer) {
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes;

    // Ask the customer how much they want to deposit
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter the amount to deposit: ");
    write(connFD, writeBuffer, strlen(writeBuffer));

    // Read the deposit amount
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    float depositAmount = atof(readBuffer);

    // Lock the customer's account before making any changes
    int customerFileFD = open(CUSTOMER_FILE, O_RDWR);
    if (customerFileFD == -1) {
        perror("Error opening customer file");
        return;
    }
    struct flock lock = {F_WRLCK, SEEK_SET, customer->id * sizeof(struct Customer), sizeof(struct Customer), getpid()};
    fcntl(customerFileFD, F_SETLKW, &lock);

    // Update the customer's balance
    customer->accountBalance += depositAmount;

    // Save the updated balance
    lseek(customerFileFD, customer->id * sizeof(struct Customer), SEEK_SET);
    write(customerFileFD, customer, sizeof(struct Customer));

    // Unlock the account and close the file
    lock.l_type = F_UNLCK;
    fcntl(customerFileFD, F_SETLK, &lock);
    close(customerFileFD);

    // Inform the customer
    bzero(writeBuffer, sizeof(writeBuffer));
    sprintf(writeBuffer, "Deposit successful! Your new balance is: %.2f\n", customer->accountBalance);
    write(connFD, writeBuffer, strlen(writeBuffer));
}

// Function to withdraw money
void withdraw_money(int connFD, struct Customer *customer) {
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes;

    // Ask the customer how much they want to withdraw
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter the amount to withdraw: ");
    write(connFD, writeBuffer, strlen(writeBuffer));

    // Read the withdrawal amount
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    float withdrawAmount = atof(readBuffer);

    // Lock the customer's account
    int customerFileFD = open(CUSTOMER_FILE, O_RDWR);
    if (customerFileFD == -1) {
        perror("Error opening customer file");
        return;
    }
    struct flock lock = {F_WRLCK, SEEK_SET, customer->id * sizeof(struct Customer), sizeof(struct Customer), getpid()};
    fcntl(customerFileFD, F_SETLKW, &lock);

    // Check if the customer has sufficient funds
    if (customer->accountBalance >= withdrawAmount) {
        customer->accountBalance -= withdrawAmount;

        // Save the updated balance
        lseek(customerFileFD, customer->id * sizeof(struct Customer), SEEK_SET);
        write(customerFileFD, customer, sizeof(struct Customer));

        // Inform the customer
        bzero(writeBuffer, sizeof(writeBuffer));
        sprintf(writeBuffer, "Withdrawal successful! Your new balance is: %.2f\n", customer->accountBalance);
    } else {
        // Insufficient funds
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "Insufficient funds. Withdrawal failed.\n");
    }

    // Unlock the account and close the file
    lock.l_type = F_UNLCK;
    fcntl(customerFileFD, F_SETLK, &lock);
    close(customerFileFD);

    // Send the response to the customer
    write(connFD, writeBuffer, strlen(writeBuffer));
}

// Function to transfer funds
void transfer_funds(int connFD, struct Customer *customer) {
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes;

    // Ask the customer for the target account ID and amount to transfer
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter the target account ID: ");
    write(connFD, writeBuffer, strlen(writeBuffer));

    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    int targetAccountID = atoi(readBuffer);

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter the amount to transfer: ");
    write(connFD, writeBuffer, strlen(writeBuffer));

    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    float transferAmount = atof(readBuffer);

    // Lock both accounts
    int customerFileFD = open(CUSTOMER_FILE, O_RDWR);
    if (customerFileFD == -1) {
        perror("Error opening customer file");
        return;
    }

    // Lock the source customer's account
    struct flock lockSource = {F_WRLCK, SEEK_SET, customer->id * sizeof(struct Customer), sizeof(struct Customer), getpid()};
    fcntl(customerFileFD, F_SETLKW, &lockSource);

    // Check if the customer has sufficient funds
    if (customer->accountBalance >= transferAmount) {
        // Find the target customer
        struct Customer targetCustomer;
        lseek(customerFileFD, targetAccountID * sizeof(struct Customer), SEEK_SET);
        ssize_t bytesRead = read(customerFileFD, &targetCustomer, sizeof(struct Customer));
        if (bytesRead == -1) {
            perror("Error reading target customer data");
            // Unlock source account before returning
            lockSource.l_type = F_UNLCK;
            fcntl(customerFileFD, F_SETLK, &lockSource);
            close(customerFileFD);
            return;
        }

        // Lock the target customer's account
        struct flock lockTarget = {F_WRLCK, SEEK_SET, targetCustomer.id * sizeof(struct Customer), sizeof(struct Customer), getpid()};
        fcntl(customerFileFD, F_SETLKW, &lockTarget);

        // Transfer funds
        customer->accountBalance -= transferAmount;
        targetCustomer.accountBalance += transferAmount;

        // Update both accounts
        lseek(customerFileFD, customer->id * sizeof(struct Customer), SEEK_SET);
        write(customerFileFD, customer, sizeof(struct Customer));
        lseek(customerFileFD, targetCustomer.id * sizeof(struct Customer), SEEK_SET);
        write(customerFileFD, &targetCustomer, sizeof(struct Customer));

        // Unlock both accounts
        lockTarget.l_type = F_UNLCK;
        fcntl(customerFileFD, F_SETLK, &lockTarget);
        lockSource.l_type = F_UNLCK;
        fcntl(customerFileFD, F_SETLK, &lockSource);

        // Inform the customer
        bzero(writeBuffer, sizeof(writeBuffer));
        sprintf(writeBuffer, "Transfer successful! Your new balance is: %.2f\n", customer->accountBalance);
    } else {
        // Insufficient funds
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "Insufficient funds. Transfer failed.\n");

        // Unlock source account
        lockSource.l_type = F_UNLCK;
        fcntl(customerFileFD, F_SETLK, &lockSource);
    }

    close(customerFileFD);

    // Send the response to the customer
    write(connFD, writeBuffer, strlen(writeBuffer));
}

// Function to apply for a loan
void apply_for_loan(int connFD, struct Customer *customer) {
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes;

    // Ask the customer for the loan amount
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter the loan amount: ");
    write(connFD, writeBuffer, strlen(writeBuffer));

    // Read the loan amount
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    float loanAmount = atof(readBuffer);

    // Update the loan amount in the customer's record
    customer->loanAmount += loanAmount;

    // Save the updated loan amount
    int customerFileFD = open(CUSTOMER_FILE, O_RDWR);
    if (customerFileFD == -1) {
        perror("Error opening customer file");
        return;
    }
    struct flock lock = {F_WRLCK, SEEK_SET, customer->id * sizeof(struct Customer), sizeof(struct Customer), getpid()};
    fcntl(customerFileFD, F_SETLKW, &lock);

    lseek(customerFileFD, customer->id * sizeof(struct Customer), SEEK_SET);
    write(customerFileFD, customer, sizeof(struct Customer));

    // Unlock the account and close the file
    lock.l_type = F_UNLCK;
    fcntl(customerFileFD, F_SETLK, &lock);
    close(customerFileFD);

    // Inform the customer
    bzero(writeBuffer, sizeof(writeBuffer));
    sprintf(writeBuffer, "Loan application successful! Your current loan amount is: %.2f\n", customer->loanAmount);
    write(connFD, writeBuffer, strlen(writeBuffer));
}

// Function to change customer password
void change_customer_password(int connFD, struct Customer *customer) {
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes;

    // Ask the customer for the new password
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter your new password: ");
    write(connFD, writeBuffer, strlen(writeBuffer));

    // Read the new password
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));

    // Hash the new password
    char *hashedPassword = crypt(readBuffer, SALT_BAE);

    // Update the password
    strcpy(customer->password, hashedPassword);

    // Save the updated password
    int customerFileFD = open(CUSTOMER_FILE, O_RDWR);
    if (customerFileFD == -1) {
        perror("Error opening customer file");
        return;
    }
    struct flock lock = {F_WRLCK, SEEK_SET, customer->id * sizeof(struct Customer), sizeof(struct Customer), getpid()};
    fcntl(customerFileFD, F_SETLKW, &lock);

    lseek(customerFileFD, customer->id * sizeof(struct Customer), SEEK_SET);
    write(customerFileFD, customer, sizeof(struct Customer));

    // Unlock the account and close the file
    lock.l_type = F_UNLCK;
    fcntl(customerFileFD, F_SETLK, &lock);
    close(customerFileFD);

    // Inform the customer
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Password changed successfully.\n");
    write(connFD, writeBuffer, strlen(writeBuffer));
}

// Function to add feedback
void add_feedback(int connFD, struct Customer *customer) {
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes;

    // Ask for feedback
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter your feedback: ");
    write(connFD, writeBuffer, strlen(writeBuffer));

    // Read feedback
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));

    // Append feedback to the feedback file
    int feedbackFileFD = open(FEEDBACK_FILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (feedbackFileFD == -1) {
        perror("Error opening feedback file");
        return;
    }

    // Write the feedback along with customer ID or name
    char feedbackEntry[1100];
    sprintf(feedbackEntry, "Customer ID %d: %s\n", customer->id, readBuffer);
    write(feedbackFileFD, feedbackEntry, strlen(feedbackEntry));
    close(feedbackFileFD);

    // Inform the customer
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Thank you for your feedback!\n");
    write(connFD, writeBuffer, strlen(writeBuffer));
}

// Function to view transaction history
void view_transaction_history(int connFD, struct Customer *customer) {
    char writeBuffer[1000];
    ssize_t writeBytes;

    // Build the transaction history file name based on customer ID
    char transactionFileName[100];
    sprintf(transactionFileName, "transaction_%d.txt", customer->id);

    // Open the transaction history file for the customer
    int transactionFileFD = open(transactionFileName, O_RDONLY);
    if (transactionFileFD < 0) {
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "Transaction history not found.\n");
        write(connFD, writeBuffer, strlen(writeBuffer));
        return;
    }

    // Read and send the transaction history
    ssize_t bytesRead;
    while ((bytesRead = read(transactionFileFD, writeBuffer, sizeof(writeBuffer))) > 0) {
        write(connFD, writeBuffer, bytesRead);
        bzero(writeBuffer, sizeof(writeBuffer));
    }
    close(transactionFileFD);
}

