/*
======================================================================================================================================================================
Name : handsonprog34b.c
Author : BHANUJA BHATT
Description : Write a program to create a concurrent server.
a. use fork
b. use pthread_create
Date: 14 sep, 2024.
======================================================================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// Thread function to handle a client connection
void *handle_client(void *arg) {
    int new_socket = *((int *)arg);
    free(arg);  // Free the dynamically allocated memory for the socket

    char buffer[BUFFER_SIZE] = {0};
    int bytes_read = read(new_socket, buffer, BUFFER_SIZE);
    if (bytes_read > 0) {
        printf("Message from client: %s\n", buffer);
        const char *response = "Hello from server (via pthread)";
        send(new_socket, response, strlen(response), 0);
    }
    close(new_socket);
    return NULL;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listening for incoming connections
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }

        // Dynamically allocate memory for the new socket to pass to the thread
        int *new_sock = malloc(sizeof(int));
        *new_sock = new_socket;

        // Create a new thread to handle the client
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, new_sock) != 0) {
            perror("Failed to create thread");
            close(new_socket);
            free(new_sock);
        } else {
            // Detach the thread so that it can clean up after itself
            pthread_detach(thread_id);
        }
    }

    close(server_fd);
    return 0;
}

