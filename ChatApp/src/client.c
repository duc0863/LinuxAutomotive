#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netdb.h>
#define BUFFER_SIZE 1024

int sock = -1;  // Socket của client

// get message form server
void *receive_message(void *arg) {
    char buffer[BUFFER_SIZE];
    while (1) {
        int bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            printf("\nReceived from server: %s\n", buffer);
            printf("Enter your command: ");
            fflush(stdout);  // Đảm bảo prompt không bị che khuất
        } else if (bytes_received == 0) {
            printf("Server disconnected.\n");
            close(sock);
            sock = -1;
            break;
        } else {
            perror("Recv failed");
            break;
        }
    }
    return NULL;
}

// command
void print_help() {
    printf("Use the commands below:\n");
    printf(" help                : display user interface options\n");
    printf(" myip                : display IP address of this app\n");
    printf(" myport              : display the port used by this app\n");
    printf(" connect <ip> <port> : connect to a server\n");
    printf(" send <message>      : send a message to the connected server\n");
    printf(" terminate           : terminate the connection to the server\n");
    printf(" exit                : close the app\n");
}

// Get IP of client
void get_my_ip() {
    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;

    if (gethostname(hostbuffer, sizeof(hostbuffer)) == -1) {
        perror("Get hostname failed");
        return;
    }

    host_entry = gethostbyname(hostbuffer);
    if (host_entry == NULL) {
        perror("Get host entry failed");
        return;
    }

    IPbuffer = inet_ntoa(*((struct in_addr *)host_entry->h_addr_list[0]));
    printf("IP Address: %s\n", IPbuffer);
}

// Get port of client
void get_my_port() {
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);

    if (getsockname(sock, (struct sockaddr *)&sin, &len) == -1) {
        perror("getsockname failed");
        return;
    }

    printf("Client port: %d\n", ntohs(sin.sin_port));
}

// connect to server
void connect_to_server(char *ip, int port) {
    struct sockaddr_in server_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        sock = -1;
        return;
    }

    printf("Connected to %s:%d\n", ip, port);
}

int main() {
    char command[BUFFER_SIZE];
    pthread_t receive_thread;

    printf("Welcome to the client application.\n");
    printf("Type 'help' for a list of commands.\n");

    while (1) {
        printf("\nEnter your command: ");
        fgets(command, BUFFER_SIZE, stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strncmp(command, "help", 4) == 0) {
            print_help();
        } else if (strncmp(command, "myip", 4) == 0) {
            get_my_ip();
        } else if (strncmp(command, "myport", 6) == 0) {
            get_my_port();
        } else if (strncmp(command, "connect", 7) == 0) {
            char ip[INET_ADDRSTRLEN];
            int port;
            sscanf(command + 8, "%s %d", ip, &port);

            connect_to_server(ip, port);

            // pthread to handle message
            pthread_create(&receive_thread, NULL, receive_message, NULL);
        } else if (strncmp(command, "send", 4) == 0) {
            if (sock == -1) {
                printf("No active connection.\n");
                continue;
            }

            char message[BUFFER_SIZE];
            sscanf(command + 5, "%[^\n]", message);
            send(sock, message, strlen(message), 0);
            printf("Message sent.\n");
        } else if (strncmp(command, "terminate", 9) == 0) {
            if (sock == -1) {
                printf("No active connection to terminate.\n");
                continue;
            }

            close(sock);
            sock = -1;
            printf("Connection terminated.\n");
        } else if (strncmp(command, "exit", 4) == 0) {
            if (sock != -1) {
                close(sock);
            }
            printf("Exiting the application...\n");
            break;
        } else {
            printf("Invalid command. Type 'help' for a list of commands.\n");
        }
    }

    return 0;
}
