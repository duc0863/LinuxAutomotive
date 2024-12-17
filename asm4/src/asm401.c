#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_1(void* ctx){
    pthread_t id = pthread_self();
    printf("Hi, thread 1 is running! - Thread ID : %ld\n", id);
    printf("Thread 1 is sleeping\n");
    sleep(5);
    return NULL;
}
void* thread_2(void* ctx){
    pthread_t id = pthread_self();
    printf("Hi, thread 2 completed successfully! - Thread ID : %ld\n", id);
    
    return NULL;
}

int main(){
    pthread_t tid1, tid2;
    
    // Tạo các thread
    pthread_create(&tid1, NULL, thread_1, NULL);
    pthread_create(&tid2, NULL, thread_2, NULL);
    
    // Chờ các thread kết thúc
    printf("Waiting.... !\n");
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("Done!\n");
    return 0;
}
