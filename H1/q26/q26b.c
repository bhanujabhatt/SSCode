#include <stdio.h>
#include <stdlib.h>

int main() {
    // Path to the executable
    char *program_path = "./a.out";
    // Argument to pass
    char *argument = "name";

    // Create the command string
    char command[100];
    snprintf(command, sizeof(command), "%s %s", program_path, argument);

    // Execute the program with the argument
    int execution_status = system(command);

    if (execution_status == -1) {
        printf("Error executing the program.\n");
    } else {
        // Check if the program executed successfully
        if (WIFEXITED(execution_status) && WEXITSTATUS(execution_status) == 0) {
            printf("Program executed successfully.\n");
        } else {
            printf("Program did not execute successfully.\n");
        }
    }

    return 0;
}

