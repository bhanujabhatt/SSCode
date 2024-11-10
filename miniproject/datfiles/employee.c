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

void create_employee_file() {
    int fd = open("employee.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct User employee;

    // Example data
    employee.id = 1;
    strcpy(employee.name, "John Employee");
    strcpy(employee.login, "employee-1");
    strcpy(employee.password, "employeePass1");

    // Write employee data to file
    ssize_t writtenBytes = write(fd, &employee, sizeof(employee));
    if (writtenBytes == -1) {
        perror("Error writing to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Add more records as needed
    employee.id = 2;
    strcpy(employee.name, "Jane Employee");
    strcpy(employee.login, "employee-2");
    strcpy(employee.password, "employeePass2");
    write(fd, &employee, sizeof(employee));

    close(fd);
    printf("Employee data successfully written to file.\n");
}

int main() {
    create_employee_file();  // Call the function to create and write the employee file
    return 0;                // Return 0 to indicate successful program execution
}

