#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

/*
yêu cầu: Viết chương trình tạo một bộ đếm thời gian bằng cách sử dụng tín hiệu SIGALRM.
Sử dụng hàm alarm() để đặt thời gian kích hoạt SIGALRM mỗi giây.
Khi nhận tín hiệu SIGALRM, chương trình sẽ tăng biến đếm và in ra dòng "Timer: <giây> seconds".
Dừng chương trình sau khi đếm đến 10 giây.
Gợi ý: Sử dụng hàm signal() để đăng ký xử lý tín hiệu SIGALRM, và đặt alarm(1) để bộ đếm lặp lại hàng giây.
Câu hỏi: Điều gì xảy ra nếu không gọi lại alarm(1) trong hàm xử lý?

*/
/*
 SIGALRM      P1990      Term    Timer signal from alarm(2)
*/
int countSignal = 0;

void SIGALRM_Handler(int sig){
    
    printf("Timer: <%d> seconds\n",countSignal++);

    if(countSignal < 11){
        alarm(3);
    }
    else{
        exit(0);
    };
    
}

int main() {

    
    signal(SIGALRM, SIGALRM_Handler);
    
    alarm(3);

    printf("waiting for SIGALRM....\n");
        
        
    while (1) {
        
    }
    
    return 0;
}
