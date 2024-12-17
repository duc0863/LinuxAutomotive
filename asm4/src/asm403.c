#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

//global variables
int buffer;
int dataReady = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

//define function
static int random_number() ;

void* Producer(void* ctx){
    for(int i = 0; i < 10; i++){
        pthread_mutex_lock(&mutex);
        
        buffer = random_number();
        //dataReady = 1;
        printf("Producer: %d\n",  buffer);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    return NULL;
}

void* Consumer(void* ctx){
    //sleep(2);
    while(1){
        pthread_mutex_lock(&mutex);
        while (!dataReady) {       // Chờ tín hiệu nếu buffer chưa sẵn sàng
            pthread_cond_wait(&cond, &mutex);
        }
        
        printf("\tConsumer: %d\n",  buffer);
        dataReady = 0;
        pthread_mutex_unlock(&mutex);
    }
    
    return NULL;
}


int main(){
    srand(time(NULL));

    pthread_t tid1, tid2;
    
    // create thread
    pthread_create(&tid1, NULL, Producer, NULL);
    pthread_create(&tid2, NULL, Consumer, NULL);

    
    //join thread to thread main
    pthread_join(tid1, NULL);
    //pthread_join(tid2, NULL);

    pthread_cancel(tid2);


    return 0;
}


static int random_number() {
    return rand() % 10 + 1; // Số ngẫu nhiên từ 1 đến 10
}