#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

//global variables
int data = 0;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER; //read-write lock

//thread for reading
void* thread_1(void* ctx){
    pthread_rwlock_rdlock(&rwlock);
    printf("Thread 1 is reading data: %d\n", data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void* thread_2(void* ctx){
    printf("Thread 2 is reading data: %d\n", data);
    return NULL;
}

void* thread_3(void* ctx){

    printf("Thread 3 is reading data: %d\n", data);
    return NULL;
}
//thread for writing
void* thread_4(void* ctx){
    pthread_rwlock_wrlock(&rwlock);
    data++;
    printf("Thread 4 is writing data\n");
    printf("Thread 4: New data is  %d\n", data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}
void* thread_5(void* ctx){
    pthread_rwlock_wrlock(&rwlock);
    
    data++;
    printf("Thread 5 is writing data\n");
    printf("Thread 5: New data is  %d\n", data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

int main(){
    
    pthread_t tid1, tid2, tid3, tid4, tid5;
    
    // create thread
    pthread_create(&tid1, NULL, thread_1, NULL); //r
    pthread_create(&tid2, NULL, thread_2, NULL); //r
    pthread_create(&tid3, NULL, thread_3, NULL); //r
    pthread_create(&tid4, NULL, thread_4, NULL); //w
    pthread_create(&tid5, NULL, thread_5, NULL); //w
    
    //join thread to thread main
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);

    return 0;
}
