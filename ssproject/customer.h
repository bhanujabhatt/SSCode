#ifndef CUSTOMER_FUNCTIONS
#define CUSTOMER_FUNCTIONS

#include <sys/ipc.h>
#include <sys/sem.h>
#include "common.h"
#include"constants.h"



struct Customer loggedInCustomer;
struct Transaction transaction;
struct LoanApplication loan;
struct Feedback customerfeedback;
struct flock lock;

int semIdentifier;



bool customer_operation_handler(int connFD);
bool get_balance(int connFD);
bool deposit(int connFD);
int write_transaction_to_file(int accountNumber, long int oldBalance, long int newBalance, bool operation);
void write_transaction_to_array(int *transactionArray, int ID);
bool withdraw(int connFD);
bool lock_critical_section(struct sembuf *semOp);
bool unlock_critical_section(struct sembuf *sem_op);
int transferFunds(int fromCustomerID, int toCustomerID, float amount);
int applyForLoan(int customerID, float loanAmount)
int addFeedback(int customerID, char* feedbackText)
bool change_password(int connFD);
bool lock_critical_section(struct sembuf *semOp);
bool unlock_critical_section(struct sembuf *sem_op);

bool customer_operation_handler(int connFD)
{
    if (login_handler(ROLE_CUSTOMER, connFD, &loggedInCustomer))
    {
        ssize_t writeBytes, readBytes;            // Number of bytes read from / written to the client
        char readBuffer[1000], writeBuffer[1000]; // A buffer used for reading & writing to the client

        // Get a semaphore for the user
        key_t semKey = ftok(CUSTOMER_FILE, loggedInCustomer.account); // Generate a key based on the account number hence, different customers will have different semaphores

        union semun
        {
            int val; // Value of the semaphore
        } semSet;

        int semctlStatus;
        semIdentifier = semget(semKey, 1, 0); // Get the semaphore if it exists
        if (semIdentifier == -1)
        {
            semIdentifier = semget(semKey, 1, IPC_CREAT | 0700); // Create a new semaphore
            if (semIdentifier == -1)
            {
                perror("Error while creating semaphore!");
                _exit(1);
            }

            semSet.val = 1; // Set a binary semaphore
            semctlStatus = semctl(semIdentifier, 0, SETVAL, semSet);
            if (semctlStatus == -1)
            {
                perror("Error while initializing a binary sempahore!");
                _exit(1);
            }
        }

        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, CUSTOMER_LOGIN_SUCCESS);
        while (1)
        {
            strcat(writeBuffer, "\n");
            strcat(writeBuffer, CUSTOMER_MENU);
            writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
            if (writeBytes == -1)
            {
                perror("Error while writing CUSTOMER_MENU to client!");
                return false;
            }
            bzero(writeBuffer, sizeof(writeBuffer));

            bzero(readBuffer, sizeof(readBuffer));
            readBytes = read(connFD, readBuffer, sizeof(readBuffer));
            if (readBytes == -1)
            {
                perror("Error while reading client's choice for CUSTOMER_MENU");
                return false;
            }

            // printf("READ BUFFER : %s\n", readBuffer);
            int choice = atoi(readBuffer);
            // printf("CHOICE : %d\n", choice);
            switch (choice)
            {
            case 1:
                 get_balance(connFD);
                break;
            case 2:
                deposit(connFD);
                break;
            case 3:
                withdraw(connFD);
                break;
            case 4:
{
    int toCustomerID;
    float amount;
    char writeBuffer[1000], readBuffer[1000];
    ssize_t writeBytes, readBytes;

    // Ask for the recipient customer ID
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter recipient customer ID: ");
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    if (writeBytes == -1) {
        perror("Error writing recipient ID prompt to client");
        return false;
    }

    // Read the recipient customer ID
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (readBytes == -1) {
        perror("Error reading recipient customer ID from client");
        return false;
    }
    toCustomerID = atoi(readBuffer);

    // Ask for the transfer amount
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter the amount to transfer: ");
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    if (writeBytes == -1) {
        perror("Error writing transfer amount prompt to client");
        return false;
    }

    // Read the transfer amount
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (readBytes == -1) {
        perror("Error reading transfer amount from client");
        return false;
    }
    amount = atof(readBuffer);

    // Perform the transfer
    int transferResult = transferFunds(loggedInCustomer.ID, toCustomerID, amount);

    if (transferResult == 0) {
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "Transfer successful!\n");
        write(connFD, writeBuffer, strlen(writeBuffer));
    } else {
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "Transfer failed. Please check the recipient ID and balance.\n");
        write(connFD, writeBuffer, strlen(writeBuffer));
    }
    break;
}             
                break;
            case 5:
{
    float loanAmount;
    char writeBuffer[1000], readBuffer[1000];
    ssize_t writeBytes, readBytes;

    // Ask the customer for the loan amount
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter the loan amount you want to apply for: ");
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    if (writeBytes == -1) {
        perror("Error writing loan amount prompt to client");
        return false;
    }

    // Read the loan amount from the client
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (readBytes == -1) {
        perror("Error reading loan amount from client");
        return false;
    }
    loanAmount = atof(readBuffer);

    // Call the applyForLoan function
    int loanResult = applyForLoan(loggedInCustomer.ID, loanAmount);

    // Check the result of the loan application
    if (loanResult == 0) {
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "Loan application submitted successfully!\n");
        write(connFD, writeBuffer, strlen(writeBuffer));
    } else {
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "Loan application failed. Please try again.\n");
        write(connFD, writeBuffer, strlen(writeBuffer));
    }
    break;
}

                
                break;
            case 6:bool change_password(int connFD);

                

		break;

	    case 7:
{
    char feedbackText[500]; // To hold the customer's feedback
    char writeBuffer[1000], readBuffer[1000];
    ssize_t writeBytes, readBytes;

    // Prompt the customer to enter their feedback
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter your feedback: ");
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    if (writeBytes == -1) {
        perror("Error writing feedback prompt to client");
        return false;
    }

    // Read the feedback from the client
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (readBytes == -1) {
        perror("Error reading feedback from client");
        return false;
    }
    strcpy(feedbackText, readBuffer);

    // Call the addFeedback function to store the feedback
    int feedbackResult = addFeedback(loggedInCustomer.ID, feedbackText);

    // Notify the user whether feedback submission was successful
    if (feedbackResult == 0) {
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "Feedback submitted successfully!\n");
        write(connFD, writeBuffer, strlen(writeBuffer));
    } else {
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "Failed to submit feedback. Please try again.\n");
        write(connFD, writeBuffer, strlen(writeBuffer));
    }
    break;
}

                

                break;
	   case 8:
// get_transaction_details(connFD, loggedInCustomer.account);

                break;

            default:
                writeBytes = write(connFD, CUSTOMER_LOGOUT, strlen(CUSTOMER_LOGOUT));
                return false;
            }
        }
    }
    else
    {
        // CUSTOMER LOGIN FAILED
        return false;
    }
    return true;
}
bool get_balance(int connFD)
{
    char buffer[1000];
    struct account account;
    account.accountNumber = loggedInCustomer.account;
    if (get_account_details(connFD, &account))
    {
        bzero(buffer, sizeof(buffer));
        if (account.active)
        {
            sprintf(buffer, "You have ₹ %ld imaginary money in our bank!^", account.balance);
            write(connFD, buffer, strlen(buffer));
        }
        else
            write(connFD, ACCOUNT_DEACTIVATED, strlen(ACCOUNT_DEACTIVATED));
        read(connFD, buffer, sizeof(buffer)); // Dummy read
    }
    else
    {
        // ERROR while getting balance
        return false;
    }
}
bool deposit(int connFD)
{
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes, writeBytes;

    struct Account account;
    account.accountNumber = loggedInCustomer.account;

    long int depositAmount = 0;

    // Lock the critical section
    struct sembuf semOp;
    lock_critical_section(&semOp);

    if (get_account_details(connFD, &account))
    {
        
        if (account.active)
        {

            writeBytes = write(connFD, DEPOSIT_AMOUNT, strlen(DEPOSIT_AMOUNT));
            if (writeBytes == -1)
            {
                perror("Error writing DEPOSIT_AMOUNT to client!");
                unlock_critical_section(&semOp);
                return false;
            }

            bzero(readBuffer, sizeof(readBuffer));
            readBytes = read(connFD, readBuffer, sizeof(readBuffer));
            if (readBytes == -1)
            {
                perror("Error reading deposit money from client!");
                unlock_critical_section(&semOp);
                return false;
            }

            depositAmount = atol(readBuffer);
            if (depositAmount != 0)
            {

                int newTransactionID = write_transaction_to_file(account.accountNumber, account.balance, account.balance + depositAmount, 1);
                write_transaction_to_array(account.transactions, newTransactionID);

                account.balance += depositAmount;

                int accountFileDescriptor = open(ACCOUNT_FILE, O_WRONLY);
                off_t offset = lseek(accountFileDescriptor, account.accountNumber * sizeof(struct Account), SEEK_SET);

                struct flock lock = {F_WRLCK, SEEK_SET, offset, sizeof(struct Account), getpid()};
                int lockingStatus = fcntl(accountFileDescriptor, F_SETLKW, &lock);
                if (lockingStatus == -1)
                {
                    perror("Error obtaining write lock on account file!");
                    unlock_critical_section(&semOp);
                    return false;
                }

                writeBytes = write(accountFileDescriptor, &account, sizeof(struct Account));
                if (writeBytes == -1)
                {
                    perror("Error storing updated deposit money in account record!");
                    unlock_critical_section(&semOp);
                    return false;
                }

                lock.l_type = F_UNLCK;
                fcntl(accountFileDescriptor, F_SETLK, &lock);

                write(connFD, DEPOSIT_AMOUNT_SUCCESS, strlen(DEPOSIT_AMOUNT_SUCCESS));
                read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read

                get_balance(connFD);

                unlock_critical_section(&semOp);

                return true;
            }
            else
                writeBytes = write(connFD, DEPOSIT_AMOUNT_INVALID, strlen(DEPOSIT_AMOUNT_INVALID));
        }
        else
            write(connFD, ACCOUNT_DEACTIVATED, strlen(ACCOUNT_DEACTIVATED));
        read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read

        unlock_critical_section(&semOp);
    }
    else
    {
        // FAIL
        unlock_critical_section(&semOp);
        return false;
    }
}
void write_transaction_to_array(int *transactionArray, int ID)
{
    // Check if there's any free space in the array to write the new transaction ID
    int iter = 0;
    while (transactionArray[iter] != -1)
        iter++;

    if (iter >= MAX_TRANSACTIONS)
    {
        // No space
        for (iter = 1; iter < MAX_TRANSACTIONS; iter++)
            // Shift elements one step back discarding the oldest transaction
            transactionArray[iter - 1] = transactionArray[iter];
        transactionArray[iter - 1] = ID;
    }
    else
    {
        // Space available
        transactionArray[iter] = ID;
    }
}

int write_transaction_to_file(int accountNumber, long int oldBalance, long int newBalance, bool operation)
{
    struct Transaction newTransaction;
    newTransaction.accountNumber = accountNumber;
    newTransaction.oldBalance = oldBalance;
    newTransaction.newBalance = newBalance;
    newTransaction.operation = operation;
    newTransaction.transactionTime = time(NULL);
i
    ssize_t readBytes, writeBytes;

    int transactionFileDescriptor = open(TRANSACTION_FILE, O_CREAT | O_APPEND | O_RDWR, S_IRWXU);

    // Get most recent transaction number
    off_t offset = lseek(transactionFileDescriptor, -sizeof(struct Transaction), SEEK_END);
    if (offset >= 0)
    {
        // There exists at least one transaction record
        struct Transaction prevTransaction;
        readBytes = read(transactionFileDescriptor, &prevTransaction, sizeof(struct Transaction));

        newTransaction.transactionID = prevTransaction.transactionID + 1;
    }
    else
        // No transaction records exist
        newTransaction.transactionID = 0;

    writeBytes = write(transactionFileDescriptor, &newTransaction, sizeof(struct Transaction));

    return newTransaction.transactionID;
}
bool withdraw(int connFD)
{
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes, writeBytes;

    struct account account;
    account.accountNumber = loggedInCustomer.account;

    long int withdrawAmount = 0;

    // Lock the critical section
    struct sembuf semOp;
    lock_critical_section(&semOp);

    if (get_account_details(connFD, &account))
    {
        if (account.active)
        {

            writeBytes = write(connFD, WITHDRAW_AMOUNT, strlen(WITHDRAW_AMOUNT));
            if (writeBytes == -1)
            {
                perror("Error writing WITHDRAW_AMOUNT message to client!");
                unlock_critical_section(&semOp);
                return false;
            }

            bzero(readBuffer, sizeof(readBuffer));
            readBytes = read(connFD, readBuffer, sizeof(readBuffer));
            if (readBytes == -1)
            {
                perror("Error reading withdraw amount from client!");
                unlock_critical_section(&semOp);
                return false;
            }

            withdrawAmount = atol(readBuffer);

            if (withdrawAmount != 0 && account.balance - withdrawAmount >= 0)
            {

                int newTransactionID = write_transaction_to_file(account.accountNumber, account.balance, account.balance - withdrawAmount, 0);
                write_transaction_to_array(account.transactions, newTransactionID);

                account.balance -= withdrawAmount;

                int accountFileDescriptor = open(ACCOUNT_FILE, O_WRONLY);
                off_t offset = lseek(accountFileDescriptor, account.accountNumber * sizeof(struct Account), SEEK_SET);

                struct flock lock = {F_WRLCK, SEEK_SET, offset, sizeof(struct Account), getpid()};
                int lockingStatus = fcntl(accountFileDescriptor, F_SETLKW, &lock);
                if (lockingStatus == -1)
                {
                    perror("Error obtaining write lock on account record!");
                    unlock_critical_section(&semOp);
                    return false;
                }

                writeBytes = write(accountFileDescriptor, &account, sizeof(struct Account));
                if (writeBytes == -1)
                {
                    perror("Error writing updated balance into account file!");
                    unlock_critical_section(&semOp);
                    return false;
                }

                lock.l_type = F_UNLCK;
                fcntl(accountFileDescriptor, F_SETLK, &lock);

                write(connFD, WITHDRAW_AMOUNT_SUCCESS, strlen(WITHDRAW_AMOUNT_SUCCESS));
                read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read

                get_balance(connFD);

                unlock_critical_section(&semOp);

                return true;
            }
            else
                writeBytes = write(connFD, WITHDRAW_AMOUNT_INVALID, strlen(WITHDRAW_AMOUNT_INVALID));
        }
        else
            write(connFD, ACCOUNT_DEACTIVATED, strlen(ACCOUNT_DEACTIVATED));
        read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read

        unlock_critical_section(&semOp);
    }
    else
    {
        // FAILURE while getting account information
        unlock_critical_section(&semOp);
        return false;
    }
}

int transferFunds(int fromCustomerID, int toCustomerID, float amount) {
    // Open the file to read customer details
    int customerFileDescriptor = open("customers.txt", O_RDWR);
    if (customerFileDescriptor < 0) {
        perror("Error opening customer file");
        return -1;
    }

    struct Customer fromCustomer, toCustomer;
    bool foundFrom = false, foundTo = false;

    // Read customer records to find both customers
    while (read(customerFileDescriptor, &fromCustomer, sizeof(struct Customer)) > 0) {
        if (fromCustomer.ID == fromCustomerID) {
            foundFrom = true;
        }
        if (fromCustomer.customerID == toCustomerID) {
            foundTo = true;
            toCustomer = fromCustomer; // Store the recipient's details
        }
        if (foundFrom && foundTo) break; // Both customers found
    }

    if (!foundFrom || !foundTo) {
        close(customerFileDescriptor);
        printf("Transfer failed: Customer not found\n");
        return -1;
    }

    // Check for sufficient funds
    if (fromCustomer.accountBalance < amount) {
        close(customerFileDescriptor);
        printf("Transfer failed: Insufficient funds\n");
        return -1;
    }

    // Perform the transfer
    fromCustomer.accountBalance -= amount;
    toCustomer.accountBalance += amount;

    // Move back to the beginning of the file to write updated records
    lseek(customerFileDescriptor, -sizeof(struct Customer), SEEK_CUR);
    write(customerFileDescriptor, &fromCustomer, sizeof(struct Customer));
    // Assuming the recipient's record is sequential, you might need to read the correct position for more complex scenarios.
    // lseek(customerFileDescriptor, <position_to_toCustomer>, SEEK_SET);
    write(customerFileDescriptor, &toCustomer, sizeof(struct Customer));

    // Close the file
    close(customerFileDescriptor);

    // Log the transaction
    struct Transaction newTransaction;
    newTransaction.customerID = fromCustomerID; // The one who sends the money
    newTransaction.amount = amount;
    strcpy(newTransaction.type, "Transfer");
    newTransaction.date = time(NULL);
    newTransaction.status = true; // Assuming the operation is successful

    int transactionID = write_transaction_to_file(fromCustomerID, fromCustomer.accountBalance + amount, fromCustomer.accountBalance, true);

    newTransaction.transactionID = transactionID;

    return 0; // Success
}
int applyForLoan(int customerID, float loanAmount) {
    // Open the loan applications file to append new loan requests
    int loanFileDescriptor = open(LOAN_APPLICATION_FILE, O_CREAT | O_APPEND | O_RDWR, S_IRWXU);
    if (loanFileDescriptor < 0) {
        perror("Error opening loan application file");
        return -1;
    }

    struct LoanApplication newLoan;
    newLoan.loanID = 0; // Should be generated based on existing records, left for simplification
    newLoan.customerID = customerID;
    newLoan.loanAmount = loanAmount;
    strcpy(newLoan.status, "Pending");

    // Write the new loan application to the file
    if (write(loanFileDescriptor, &newLoan, sizeof(struct LoanApplication)) < 0) {
        perror("Error writing loan application");
        close(loanFileDescriptor);
        return -1;
    }

    close(loanFileDescriptor);
    printf("Loan application submitted successfully.\n");
    return 0; // Success
}
int addFeedback(int customerID, char* feedbackText) {
    // Open the feedback file to append new feedback
    int feedbackFileDescriptor = open(FEEDBACK_FILE, O_CREAT | O_APPEND | O_RDWR, S_IRWXU);
    if (feedbackFileDescriptor < 0) {
        perror("Error opening feedback file");
        return -1;
    }

    struct Feedback newFeedback;
    newFeedback.feedbackID = 0; // Should be generated based on existing records
    newFeedback.customerID = customerID;
    strncpy(newFeedback.feedbackText, feedbackText, sizeof(newFeedback.feedbackText) - 1);
    newFeedback.feedbackText[sizeof(newFeedback.feedbackText) - 1] = '\0'; // Null terminate
    newFeedback.date = time(NULL);

    // Write the new feedback to the file
    if (write(feedbackFileDescriptor, &newFeedback, sizeof(struct Feedback)) < 0) {
        perror("Error writing feedback");
        close(feedbackFileDescriptor);
        return -1;
    }

    close(feedbackFileDescriptor);
    printf("Feedback submitted successfully.\n");
    return 0; // Success
}

bool change_password(int connFD) {
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], newPassword[1000];

    // Lock the critical section
    struct sembuf semOp = {0, -1, SEM_UNDO};
    int semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1) {
        perror("Error while locking critical section");
        return false;
    }

    // Request old password from user
    writeBytes = write(connFD, PASSWORD_CHANGE_OLD_PASS, strlen(PASSWORD_CHANGE_OLD_PASS));
    if (writeBytes == -1) {
        perror("Error writing PASSWORD_CHANGE_OLD_PASS message to client!");
        unlock_critical_section(&semOp);
        return false;
    }

    // Read old password from user
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (readBytes == -1) {
        perror("Error reading old password response from client");
        unlock_critical_section(&semOp);
        return false;
    }

    // Check if the old password matches the stored password
    if (strcmp(readBuffer, loggedInCustomer.password) == 0) {
        // Old password matches
        writeBytes = write(connFD, PASSWORD_CHANGE_NEW_PASS, strlen(PASSWORD_CHANGE_NEW_PASS));
        if (writeBytes == -1) {
            perror("Error writing PASSWORD_CHANGE_NEW_PASS message to client!");
            unlock_critical_section(&semOp);
            return false;
        }

        // Read new password from user
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        if (readBytes == -1) {
            perror("Error reading new password response from client");
            unlock_critical_section(&semOp);
            return false;
        }

        // Store new password temporarily
        strcpy(newPassword, readBuffer);

        // Request re-entering new password
        writeBytes = write(connFD, PASSWORD_CHANGE_NEW_PASS_RE, strlen(PASSWORD_CHANGE_NEW_PASS_RE));
        if (writeBytes == -1) {
            perror("Error writing PASSWORD_CHANGE_NEW_PASS_RE message to client!");
            unlock_critical_section(&semOp);
            return false;
        }

        // Read re-entered new password from user
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        if (readBytes == -1) {
            perror("Error reading new password reenter response from client");
            unlock_critical_section(&semOp);
            return false;
        }

        // Check if new passwords match
        if (strcmp(readBuffer, newPassword) == 0) {
            // New passwords match, update the stored password
            strcpy(loggedInCustomer.password, newPassword);

            // Open customer file to update the password
            int customerFileDescriptor = open(CUSTOMER_FILE, O_WRONLY);
            if (customerFileDescriptor == -1) {
                perror("Error opening customer file!");
                unlock_critical_section(&semOp);
                return false;
            }

            // Seek to the position of the customer record to update
            off_t offset = lseek(customerFileDescriptor, loggedInCustomer.id * sizeof(struct Customer), SEEK_SET);
            if (offset == -1) {
                perror("Error seeking to the customer record!");
                unlock_critical_section(&semOp);
                return false;
            }

            struct flock lock = {F_WRLCK, SEEK_SET, offset, sizeof(struct Customer), getpid()};
            int lockingStatus = fcntl(customerFileDescriptor, F_SETLKW, &lock);
            if (lockingStatus == -1) {
                perror("Error obtaining write lock on customer record!");
                unlock_critical_section(&semOp);
                return false;
            }

            // Write the updated customer record back to the file
            writeBytes = write(customerFileDescriptor, &loggedInCustomer, sizeof(struct Customer));
            if (writeBytes == -1) {
                perror("Error storing updated customer password into customer record!");
                unlock_critical_section(&semOp);
                return false;
            }

            // Release the lock
            lock.l_type = F_UNLCK;
            lockingStatus = fcntl(customerFileDescriptor, F_SETLK, &lock);

            close(customerFileDescriptor);

            writeBytes = write(connFD, PASSWORD_CHANGE_SUCCESS, strlen(PASSWORD_CHANGE_SUCCESS));
            readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read

            unlock_critical_section(&semOp);
            return true;
        } else {
            // New & reentered passwords don't match
            writeBytes = write(connFD, PASSWORD_CHANGE_NEW_PASS_INVALID, strlen(PASSWORD_CHANGE_NEW_PASS_INVALID));
            readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
        }
    } else {
        // Old password doesn't match
        writeBytes = write(connFD, PASSWORD_CHANGE_OLD_PASS_INVALID, strlen(PASSWORD_CHANGE_OLD_PASS_INVALID));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
    }

    unlock_critical_section(&semOp);
    return false;
}
bool lock_critical_section(struct sembuf *semOp)
{
    semOp->sem_flg = SEM_UNDO;
    semOp->sem_op = -1;
    semOp->sem_num = 0;
    int semopStatus = semop(semIdentifier, semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while locking critical section");
        return false;
    }
    return true;
}

bool unlock_critical_section(struct sembuf *semOp)
{
    semOp->sem_op = 1;
    int semopStatus = semop(semIdentifier, semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        _exit(1);
    }
    return true;
}
// =====================================================

#endif
