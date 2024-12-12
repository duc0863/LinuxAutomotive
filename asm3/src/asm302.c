#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    //check number of argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename num-bytes [r/w] \"content\"\n", argv[0]);
        return 1;
    }
    int mode = atoi(argv[1]); //convert a string to interger

    if (mode <= 0) {
        fprintf(stderr, "Error: This must be a positive integer.\n");
        return 1;
    }

    pid_t pid; //process id
    pid = fork(); //create a new process

    if(pid < 0){
        printf("Error while creating a new process!");
        exit(EXIT_FAILURE);
    } else if(pid == 0){  //child process
        printf("This is child process, process ID: %d \n", getpid());
        if(mode == 1){ //use "ls" command
            printf("Process ID: %d\n", getpid());
            fflush(stdout);
            execlp("ls", "ls", "-l", (char *) NULL);
            
        } else if (mode == 2)
        {
            printf("Process ID: %d\n", getpid());
            fflush(stdout);
            execlp("date", "date", (char *) NULL);
        }
        
    } else{               //parent process
        wait(NULL);
        printf("This is parent process, process ID: %d \n", getpid());
    }
    
    return 0;
}
