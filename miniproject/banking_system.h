// banking_system.h

#ifndef BANKING_SYSTEM_H
#define BANKING_SYSTEM_H

// Define necessary structures
struct BankEmployee {
    int id;
    char name[50];
    char password[100];
    // Other relevant fields
};

struct Customer {
    int id;
    char name[50];
    float accountBalance;
    char password[100];
    // Other relevant fields
};

// Function prototypes
void bank_employee_operation_handler(int connFD);
void add_new_customer(int connFD);
void modify_customer_details(int connFD);
void process_loan_applications(int connFD);
void approve_reject_loans(int connFD);
void view_assigned_loans(int connFD);
void view_customer_transactions(int connFD);
void change_employee_password(int connFD);
void bank_employee_operation_handler(int connFD) {
   
// Function prototypes for bank employee operations
void add_new_customer(int connFD);
void modify_customer_details(int connFD);
void process_loan_applications(int connFD);
void approve_reject_loans(int connFD);
void view_assigned_loans(int connFD);
void view_customer_transactions(int connFD);
void change_employee_password(int connFD);

// Main handler for bank employee operations
void bank_employee_operation_handler(int connFD) {
    char readBuffer[1000], writeBuffer[1000];
    ssize_t writeBytes, readBytes;

    while (1) {
        // Present the bank employee with the available options
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "\nBank Employee Menu:\n"
                            "1. Add New Customer\n"
                            "2. Modify Customer Details\n"
                            "3. Process Loan Applications\n"
                            "4. Approve/Reject Loans\n"
                            "5. View Assigned Loan Applications\n"
                            "6. View Customer Transactions\n"
                            "7. Change Password\n"
                            "8. Logout\n"
                            "9. Exit\n"
                            "Enter your choice: ");
        write(connFD, writeBuffer, strlen(writeBuffer));

        // Read the employee’s choice
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        int choice = atoi(readBuffer);

        // Handle the bank employee's choice
        switch (choice) {
            case 1:
                add_new_customer(connFD);
                break;
            case 2:
                modify_customer_details(connFD);
                break;
            case 3:
                process_loan_applications(connFD);
                break;
            case 4:
                approve_reject_loans(connFD);
                break;
            case 5:
                view_assigned_loans(connFD);
                break;
            case 6:
                view_customer_transactions(connFD);
                break;
            case 7:
                change_employee_password(connFD);
                break;
            case 8:
                // Handle employee logout
                bzero(writeBuffer, sizeof(writeBuffer));
                strcpy(writeBuffer, "You have been logged out successfully.\n");
                write(connFD, writeBuffer, strlen(writeBuffer));
                return; // Break the loop to exit the employee session
            case 9:
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

// Function to add a new customer
void add_new_customer(int connFD) {
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes;

    // Logic to add a new customer
    // Here you would collect customer details and write to the customer file

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "New customer added successfully.\n");
    write(connFD, writeBuffer, strlen(writeBuffer));
}

// Function to modify customer details
void modify_customer_details(int connFD) {
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes;

    // Logic to modify existing customer details
    // Here you would read the customer ID and update the details in the file

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Customer details modified successfully.\n");
    write(connFD, writeBuffer, strlen(writeBuffer));
}

// Function to process loan applications
void process_loan_applications(int connFD) {
    char writeBuffer[1000];

    // Logic to process loan applications
    // Here you would read loan applications from a file and process them

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Loan applications processed successfully.\n");
    write(connFD, writeBuffer, strlen(writeBuffer));
}

// Function to approve or reject loans
void approve_reject_loans(int connFD) {
    char writeBuffer[1000];

    // Logic to approve or reject loans
    // Here you would read a specific loan application and update its status

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Loan approved/rejected successfully.\n");
    write(connFD, writeBuffer, strlen(writeBuffer));
}

// Function to view assigned loan applications
void view_assigned_loans(int connFD) {
    char writeBuffer[1000];

    // Logic to view assigned loan applications
    // Here you would read and display the assigned loans for this employee

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Assigned loan applications displayed successfully.\n");
    write(connFD, writeBuffer, strlen(writeBuffer));
}

// Function to view customer transactions
void view_customer_transactions(int connFD) {
    char writeBuffer[1000];

    // Logic to view customer transactions
    // Here you would read the transaction history of a customer

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Customer transactions displayed successfully.\n");
    write(connFD, writeBuffer, strlen(writeBuffer));
}

// Function to change employee password
void change_employee_password(int connFD) {
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes;

    // Logic to change employee password
    // Here you would read the new password and update it

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Employee password changed successfully.\n");
    write(connFD, writeBuffer, strlen(writeBuffer));
}

}
#endif // BANKING_SYSTEM_H
