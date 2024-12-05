#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 128
int main(int argc, char *argv[]) {
    //check number of argument
    if (argc != 5) {
        fprintf(stderr, "Usage: %s filename num-bytes [r/w] \"content\"\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int num_bytes = atoi(argv[2]); //convert a string to interger
    char mode = argv[3][0]; // 'r' or 'w'
    const char *content = argv[4];

    if (num_bytes <= 0) {
        fprintf(stderr, "Error: num-bytes must be a positive integer.\n");
        return 1;
    }

    int fd;
    size_t size;

    if (mode == 'r') {
        // Read file
        char buffer[BUFFER_SIZE];
        fd = open(filename, O_RDONLY);

        if(fd == -1 ){
            printf("Error while opening file\n");
            return;
        }

        ssize_t bytes_read;

        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if(bytes_read < 0){
            printf("Error while reading file\n");
        }

        printf("%s", buffer);

        
        close(fd);

    } else if (mode == 'w') {
        // write to a file
        int fd;
        size_t size;

        fd = open(filename, O_CREAT | O_WRONLY, 0664);
        if(fd < 0){
            printf("Error while opening file\n");
            return;
        }

        size = write(fd, content, strlen(content));
        if(size < strlen(content))
            printf("Error while writing to file\n");

        close(fd);

    } else {
        printf("Error: Invalid mode. Use 'r' for read or 'w' for write.\n");
        return 1;
    }

    return 0;
}
