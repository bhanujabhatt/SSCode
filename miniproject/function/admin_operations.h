#ifndef ADMIN_OPERATIONS_H
#define ADMIN_OPERATIONS_H

#define CUSTOMER_FILE "customers.dat"
#define EMPLOYEE_FILE "employees.dat"
#define SALT_BAE "$6$salt"

#define ADMIN_LOGIN_WELCOME "Welcome Admin!"
#define ADMIN_LOGIN_ID "admin"
#define ADMIN_PASSWORD "$6$adminpass"
#define CUSTOMER_LOGIN_WELCOME "Welcome Customer!"
#define CUSTOMER_LOGIN_ID_DOESNT_EXIT "Customer login ID doesn't exist!"
#define PASSWORD "Enter Password: "
#define INVALID_LOGIN "Invalid login!"
#define INVALID_PASSWORD "Invalid password!"

struct Customer {
    char name[100];
    int id;
    double balance;
    char login[100];
    char password[100];
};

struct Employee {
    char name[100];
    int id;
    char role[50];
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

// Main function that handles admin operations
void admin_operation_handler(int connFD) {
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];
    int choice;

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
            return; // Logout and return to calling function

        case 6:
            exit(0); // Exit the program

        default:
            bzero(writeBuffer, sizeof(writeBuffer));
            strcpy(writeBuffer, "Invalid choice. Please try again.\n");
            writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
            if (writeBytes == -1) {
                perror("Error writing invalid choice message!");
                return;
            }
            break;
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

    strcat(writeBuffer, "Name: ");
    write(connFD, writeBuffer, strlen(writeBuffer));
    read(connFD, newEmployee.name, sizeof(newEmployee.name));

    strcat(writeBuffer, "ID: ");
    write(connFD, writeBuffer, strlen(writeBuffer));
    read(connFD, newEmployee.id, sizeof(newEmployee.id));

    strcat(writeBuffer, "Role: ");
    write(connFD, writeBuffer, strlen(writeBuffer));
    read(connFD, newEmployee.role, sizeof(newEmployee.role));

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
    int userType; // 1 for customer, 2 for employee
    int ID;
    struct Customer customer;
    struct Employee employee;

    bzero(readBuffer, sizeof(readBuffer));
    bzero(writeBuffer, sizeof(writeBuffer));

    // Ask admin to choose between customer or employee
    strcpy(writeBuffer, "Modify Details:\n1. Customer\n2. Employee\nEnter your choice: ");
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    if (writeBytes == -1) {
        perror("Error writing choice to client!");
        return;
    }

    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (readBytes == -1) {
        perror("Error reading user choice from client!");
        return;
    }

    userType = atoi(readBuffer); // Convert the input to integer

    // Ask for the ID of the customer or employee
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter the ID: ");
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    if (writeBytes == -1) {
        perror("Error writing ID request to client!");
        return;
    }

    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (readBytes == -1) {
        perror("Error reading ID from client!");
        return;
    }

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

        bzero(writeBuffer, sizeof(writeBuffer));
        sprintf(writeBuffer, "Current Details:\nName: %s\nID: %d\nBalance: %.2f\n", customer.name, customer.id, customer.balance);
        write(connFD, writeBuffer, strlen(writeBuffer));

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
        if (strlen(readBuffer) > 1)
            customer.balance = atof(readBuffer);

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

        bzero(writeBuffer, sizeof(writeBuffer));
        sprintf(writeBuffer, "Current Details:\nName: %s\nID: %d\nRole: %s\n", employee.name, employee.id, employee.role);
        write(connFD, writeBuffer, strlen(writeBuffer));

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
        if (strlen(readBuffer) > 1)
            strcpy(employee.role, readBuffer);

        lseek(employeeFileFD, ID * sizeof(struct Employee), SEEK_SET);
        writeBytes = write(employeeFileFD, &employee, sizeof(struct Employee));
        if (writeBytes == -1) {
            perror("Error writing updated employee record");
        }

        lock.l_type = F_UNLCK;
        fcntl(employeeFileFD, F_SETLK, &lock);
        close(employeeFileFD);
    } else {
        strcpy(writeBuffer, "Invalid choice. Please select 1 for Customer or 2 for Employee.\n");
        write(connFD, writeBuffer, strlen(writeBuffer));
    }
}

// Function to manage user roles
void manage_user_roles(int connFD) {
    ssize_t writeBytes, readBytes;
    char readBuffer[1000], writeBuffer[1000];
    struct Employee employee;
    int ID;

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter Employee ID to modify roles: ");
    write(connFD, writeBuffer, strlen(writeBuffer));
    read(connFD, readBuffer, sizeof(readBuffer));
    ID = atoi(readBuffer); // Convert the input to integer

    // Open the employee file
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

    bzero(writeBuffer, sizeof(writeBuffer));
    sprintf(writeBuffer, "Current Role: %s\nEnter new role: ", employee.role);
    write(connFD, writeBuffer, strlen(writeBuffer));

    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    strcpy(employee.role, readBuffer);

    lseek(employeeFileFD, ID * sizeof(struct Employee), SEEK_SET);
    writeBytes = write(employeeFileFD, &employee, sizeof(struct Employee));
    if (writeBytes == -1) {
        perror("Error writing updated employee role");
    }

    lock.l_type = F_UNLCK;
    fcntl(employeeFileFD, F_SETLK, &lock);
    close(employeeFileFD);
}

// Function to change the admin password
void change_admin_password(int connFD) {
    ssize_t writeBytes, readBytes;
    char readBuffer[1000], writeBuffer[1000], oldPassword[100], newPassword[100];
    struct crypt_data data;

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, "Enter old password: ");
    write(connFD, writeBuffer, strlen(writeBuffer));

    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    strcpy(oldPassword, readBuffer);

    // Verify the old password
    if (strcmp(crypt(oldPassword, SALT_BAE, &data), ADMIN_PASSWORD) != 0) {
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

    // Encrypt the new password and save it (this is just a mock, actual storage would be more secure)
    strcpy(ADMIN_PASSWORD, crypt(newPassword, SALT_BAE, &data));

    strcpy(writeBuffer, "Password changed successfully!\n");
    write(connFD, writeBuffer, strlen(writeBuffer));
}

// Function to handle admin logout
void logout_admin(int connFD) {
    char writeBuffer[1000];
    strcpy(writeBuffer, "You have been logged out successfully.\n");
    write(connFD, writeBuffer, strlen(writeBuffer));
}
#endif // ADMIN_OPERATIONS_H

