#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// Structure definition for User (specifically for Customer)
struct User {
  char name[100];
    int id;
    double balance;
    char login[100];
    char password[100];
     // Customer-specific field to store balance
};

// Function to create and write customer records to customer.dat
void create_customer_file() {
    // Open the file for writing (create it if it doesn't exist, or truncate it if it does)
    int fd = open("customer.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct User customer;

    // Example data for first customer
    customer.id = 1;
    strcpy(customer.name, "Charlie Customer");
    strcpy(customer.login, "customer-1");
    strcpy(customer.password, "custPass1");
    customer.balance = 5000.0;  // Initial balance for customer

    // Write first customer data to file
    ssize_t writtenBytes = write(fd, &customer, sizeof(customer));
    if (writtenBytes == -1) {
        perror("Error writing to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Example data for second customer
    customer.id = 2;
    strcpy(customer.name, "Dana Customer");
    strcpy(customer.login, "customer-2");
    strcpy(customer.password, "custPass2");
    customer.balance = 3000.0;  // Initial balance for second customer
    write(fd, &customer, sizeof(customer));

    // Close the file
    close(fd);
    printf("Customer data successfully written to file.\n");
}

// Main function to call the create_customer_file function
int main() {
    create_customer_file();  // Call the function to create and write customer records
    return 0;                // Return 0 to indicate successful program execution
}

