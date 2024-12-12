#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main() {
    pid_t pid; //process id
    pid = fork(); //create a new process
    if(pid < 0){
        printf("Error while creating a new process!");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){  //child process
        printf("This is child process, with process ID: %d \n", getpid());
    }
    else{               //parent process
        printf("This is parent process, with process ID: %d \n", pid);
    }

    return 0; 
    
}
