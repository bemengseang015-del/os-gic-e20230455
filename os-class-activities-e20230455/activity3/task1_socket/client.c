
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8081

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char *message = "Hello from client!";

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary
    if (inet_pton(AF_INET, "127.0.0.1",
                  &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr,
                sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Send message
    send(sock, message, strlen(message), 0);
    printf("Client: %s\n", message);

    // Receive response
    read(sock, buffer, sizeof(buffer) - 1);
    printf("Server: %s\n", buffer);

    close(sock);

    return 0;
}
