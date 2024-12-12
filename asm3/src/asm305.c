#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>



void SIGUSR1_Handler(int sig){
    printf("Child process received SIGUSR1 signal (%d)\n", sig);
    exit(0);
}

int main() {

    pid_t pid; //process id
    pid = fork(); //create a new process

    if(pid < 0){
        printf("Error while creating a new process!");
        exit(EXIT_FAILURE);
    } 
    else if(pid == 0){  //child process
        signal(SIGUSR1, SIGUSR1_Handler);
        printf("Child process is waiting for SIGUSR1... from parent process.\n");
        
        while (1) {
            printf("Child is waiting for SIGUSR1...\n");
            sleep(5); 
        }
    } 
    else{               //parent process
        sleep(2); //wait for child process running before

        kill(pid, SIGUSR1);

        sleep(30);
        
        printf("This is parent process, process ID: %d \n", getpid());
        //wait(NULL); //wait for child process ended
        printf("Parent process exiting.\n");        
    }
    
    return 0;
}
