
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

/*
BT4. Viết một chương trình có thể bỏ qua tín hiệu SIGTSTP (thường là Ctrl+Z).
Sử dụng signal() hoặc sigaction() để bắt và bỏ qua tín hiệu SIGTSTP.
Khi nhận tín hiệu SIGTSTP, chương trình sẽ không dừng mà tiếp tục chạy và in thông báo "SIGTSTP ignored".
Gợi ý: Đảm bảo chương trình sẽ tiếp tục chạy thay vì bị dừng khi nhấn Ctrl+Z.
Câu hỏi: Điều gì xảy ra nếu không xử lý tín hiệu SIGTSTP và người dùng nhấn Ctrl+Z?


*/
/*
SIGTSTP      P1990      Stop    Stop typed at terminal
*/
int countSignal = 0;

void SIGTSTP_Handler(int sig){
    printf("SIGTSTP ignored\n");

    
}

int main() {

    
        signal(SIGTSTP, SIGTSTP_Handler);

        printf("waiting for SIGTSTP...\n");
        
        while (1) {
            sleep(1);
            printf("Program running...\n");
        }
    
    return 0;
}
