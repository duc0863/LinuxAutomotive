#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
/********************************@brief**********************************
WIFEXITED(wstatus)
              returns true if the child terminated normally, that is, by
              calling exit(3) or _exit(2), or by returning from main().

WEXITSTATUS(wstatus)
              returns the exit status of the child.  This consists of
              the least significant 8 bits of the status argument that
              the child specified in a call to exit(3) or _exit(2) or as
              the argument for a return statement in main().  This macro
              should be employed only if WIFEXITED returned true.
 *************************************************************************/

#define EXIT_CODE   28

int main() {

    pid_t pid; //process id
    pid = fork(); //create a new process

    if(pid < 0){
        printf("Error while creating a new process!");
        exit(EXIT_FAILURE);
    } 
    else if(pid == 0){  //child process
        printf("This is child process, process ID: %d \n", getpid());

        printf("Child process: Exiting with code %d\n", EXIT_CODE);
        exit(EXIT_CODE); // child process ended with an exit-code selected before
    } 
    else{               //parent process
        int status;
        wait(&status);

        
        if(WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status); // Lấy mã thoát của tiến trình con
            printf("Parent process: Child process exited normally with exit-code: %d\n", exit_status);
        }
        else 
        {
            printf("Parent process: Child process didn't exit normally\n");
        }
        printf("This is parent process, process ID: %d \n", getpid());
        printf("Parent process exiting.\n");        
    }
    
    return 0;
}
