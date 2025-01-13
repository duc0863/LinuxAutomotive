#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netdb.h>

#define BUFFER_SIZE 1024
#define PORT 5000

// Client information
typedef struct {
    int socket;
    struct sockaddr_in address;
    pthread_t thread;
} client_info_t;

int server_socket = -1;  // Socket server
client_info_t clients[10]; // list client
int client_count = 0;  // Num of client is connecting

// command
void print_help() {
    printf("Use the commands below:\n");
    printf(" help                : display user interface options\n");
    printf(" myip                : display IP address of this app\n");
    printf(" myport              : display the port used by this app\n");
    printf(" list                : list IP address of clients\n");
    printf(" send <message>      : send a message to the connected client\n");
    printf(" terminate           : terminate the connection to the client\n");
    printf(" exit                : close the app\n");
}

// gets and shows IP server
void get_my_ip() {
    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;

    // get host name
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

    printf("Server IP Address: %s\n", IPbuffer);
}

// get port server
void get_my_port() {
    printf("Server is listening on port %d\n", PORT);
}

// show the list of client is connected
void list_clients() {
    printf("Connected clients:\n");
    for (int i = 0; i < client_count; i++) {
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clients[i].address.sin_addr, client_ip, sizeof(client_ip));
        printf("Client %d: %s:%d\n", i + 1, client_ip, ntohs(clients[i].address.sin_port));
    }
}

// handle commmands from terminal
void *handle_commands(void *arg) {
    char command[BUFFER_SIZE];

    while (1) {
        printf("\nEnter command: ");
        fgets(command, BUFFER_SIZE, stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strncmp(command, "help", 4) == 0) {
            print_help();
        } else if (strncmp(command, "myip", 4) == 0) {
            get_my_ip();
        } else if (strncmp(command, "myport", 6) == 0) {
            get_my_port();
        } else if (strncmp(command, "list", 4) == 0) {
            list_clients();
        } else if (strncmp(command, "send", 4) == 0) {
            if (client_count == 0) {
                printf("No client connected.\n");
                continue;
            }

            char message[BUFFER_SIZE];
            sscanf(command + 5, "%[^\n]", message);

            for (int i = 0; i < client_count; i++) {
                send(clients[i].socket, message, strlen(message), 0);
                printf("Message sent to client %d: %s\n", i + 1, message);
            }
        } else if (strncmp(command, "terminate", 9) == 0) {
            if (client_count == 0) {
                printf("No client to terminate.\n");
                continue;
            }

            close(clients[client_count - 1].socket);
            client_count--;
            printf("Last client connection terminated.\n");
        } else if (strncmp(command, "exit", 4) == 0) {
            for (int i = 0; i < client_count; i++) {
                close(clients[i].socket);
            }
            printf("Server is shutting down...\n");
            break;
        } else {
            printf("Invalid command. Type 'help' for a list of commands.\n");
        }
    }

    return NULL;
}

// handle connection from client
void *handle_client(void *arg) {
    client_info_t *client_info = (client_info_t *)arg;
    char buffer[BUFFER_SIZE];
    int bytes_received;

    while (1) {
        bytes_received = recv(client_info->socket, buffer, sizeof(buffer), 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            printf("\nReceived from client %s:%d: %s\n", 
                    inet_ntoa(client_info->address.sin_addr), 
                    ntohs(client_info->address.sin_port), 
                    buffer);
        } else if (bytes_received == 0) {
            printf("Client %s:%d disconnected.\n", 
                    inet_ntoa(client_info->address.sin_addr), 
                    ntohs(client_info->address.sin_port));
            close(client_info->socket);
            break;
        } else {
            perror("recv failed");
            break;
        }
    }

    return NULL;
}

//start server and listening
void start_server() {
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pthread_t command_thread;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        return;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        return;
    }

    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        return;
    }

    printf("Server is running. IP: ");
    get_my_ip();
    get_my_port();
    printf("Waiting for clients to connect...\n");

    // thread for command
    pthread_create(&command_thread, NULL, handle_commands, NULL);

    // accept client
    while (1) {
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        printf("New client connected: %s:%d\n", 
                inet_ntoa(client_addr.sin_addr), 
                ntohs(client_addr.sin_port));

        // save client infor
        if (client_count < 10) {
            clients[client_count].socket = client_socket;
            clients[client_count].address = client_addr;
            pthread_create(&clients[client_count].thread, NULL, handle_client, &clients[client_count]);
            client_count++;
        } else {
            printf("Max clients reached. Connection rejected.\n");
            close(client_socket);
        }
    }

    close(server_socket);
}

int main() {
    start_server();
    return 0;
}
