#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define CURSOR_POSITION		0	//set cursor position at the beginning of the file

void seek_and_write(const char *filename,const char *data, int offset){
    int fd;
    size_t size;

    //open file
    fd = open(filename, O_WRONLY | O_APPEND);
    if(fd == -1 ){
        printf("Error while opening file\n");
        return;
    }
    //seek cursor at offset position
    lseek(fd, offset,SEEK_SET);
    
    //write data to file
    size = write(fd, data, strlen(data));
    if(size < strlen(data))
        printf("Error while writing to file\n");
    
    //close file
    close(fd);

}

int main() {
    const char *filename = "asm2.txt";
    const char *data = "Hello, World!\n";
    
    seek_and_write(filename, data, CURSOR_POSITION);

    return 0; 
    
}
