
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

/*
Yêu cầu: Viết chương trình tạo hai process (cha và con) và sử dụng tín hiệu SIGUSR1 để giao tiếp giữa chúng.
Cách thực hiện
Dùng fork() để tạo process con từ process cha.
Process cha sẽ gửi tín hiệu SIGUSR1 cho process con mỗi 2 giây.
Khi nhận tín hiệu SIGUSR1, process con sẽ in ra thông báo "Received signal from parent".
Dừng chương trình sau khi đã gửi tín hiệu 5 lần.
Gợi ý: Dùng kill() để gửi tín hiệu từ process cha đến process con, và sử dụng signal() trong process con để bắt tín hiệu SIGUSR1.
Câu hỏi: Tại sao chúng ta cần sử dụng kill() để gửi tín hiệu trong bài này?

Answer: kill() cho phép process cha gửi tín hiệu đến process con một cách trực tiếp thông qua PID.
        Đây là cách duy nhất để giao tiếp bằng tín hiệu giữa hai process độc lập, 
            vì chúng không chia sẻ cùng một không gian địa chỉ.
        Nếu không dùng kill(), process cha sẽ không thể gửi tín hiệu đến process con 
            mà không dựa vào một cơ chế giao tiếp liên process khác như pipe hoặc shared memory.

*/
/*
SIGUSR1      P1990      Term    User-defined signal 1
*/
int countSignal = 0;

void SIGUSR1_Handler(int sig){
    printf("Received signal from parent\n");
}

int main() {

    pid_t pid;
    pid = fork();

    if(pid < 0){
        printf("Error while creating a new process!");
        exit(EXIT_FAILURE);
    } 
    else if(pid == 0){  //child process

        printf("Child process is waiting SIGUSR1 signal...\n");

        signal(SIGUSR1, SIGUSR1_Handler);

        while (1) {
           
        }

    } 
    else{               //parent process
        printf("Parent process is running\n");
        while(countSignal < 5){
            sleep(2); // Chờ 2 giây
            kill(pid, SIGUSR1); // Gửi tín hiệu SIGUSR1 đến process con
            printf("Parent process: Sent signal %d\n", countSignal + 1);
            countSignal++;
        }
        exit(0);
    }
    
    
    return 0;
}
