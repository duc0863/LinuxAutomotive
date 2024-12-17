#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//global variables
long long int counter = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_1(void* ctx){
    pthread_mutex_lock(&mutex);
    for(int i = 1; i <= 1000000; i++){
        counter += 1;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* thread_2(void* ctx){
    pthread_mutex_lock(&mutex);
    for(int i = 1; i <= 1000000; i++){
        counter += 1;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* thread_3(void* ctx){
    pthread_mutex_lock(&mutex);
    for(int i = 1; i <= 1000000; i++){
        counter += 1;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(){
    pthread_t tid1, tid2, tid3;
    
    // create thread
    pthread_create(&tid1, NULL, thread_1, NULL);
    pthread_create(&tid2, NULL, thread_2, NULL);
    pthread_create(&tid2, NULL, thread_3, NULL);
    
    //join thread to thread main
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    printf("Result: %lld\n", counter);

    return 0;
}
