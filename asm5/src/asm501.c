#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

/*
Yêu cầu: Viết một chương trình bắt tín hiệu SIGINT (được gửi khi nhấn Ctrl+C) và in ra thông báo khi nhận được tín hiệu này.
Sử dụng hàm signal() để đăng ký một hàm xử lý cho tín hiệu SIGINT.
Trong hàm xử lý, in ra thông báo "SIGINT received" mỗi khi nhận được tín hiệu SIGINT.
Chương trình sẽ tiếp tục chạy cho đến khi nhận được SIGINT lần thứ 3, sau đó kết thúc.
Gợi ý: Sử dụng một biến đếm toàn cục để đếm số lần tín hiệu SIGINT được nhận và kiểm tra biến này trong hàm xử lý.
Câu hỏi: Nếu bỏ qua tín hiệu SIGINT, chuyện gì sẽ xảy ra khi nhấn Ctrl+C?

*/
/*
 SIGINT       P1990      Term    Interrupt from keyboard
*/
int countSignal = 0;

void SIGINT_Handler(int sig){
    printf("received SIGINT signal (%d)\n", sig);
    countSignal++;
    if(countSignal == 3){
        exit(0);
    };
    
}

int main() {

    
        signal(SIGINT, SIGINT_Handler);

        printf("waiting for SIGINT...\n");
        
        while (1) {

        }
    
    return 0;
}
