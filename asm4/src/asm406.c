#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

//global variables
static int random_number_from_1_to_100();
static int arr[1000000];
long int sumOfArr = 0;
long int sumOriginal = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* beginning_to_quarter(void* ctx){
    pthread_mutex_lock(&mutex);
    for(int i = 0; i < 250000; i++){
        sumOfArr += arr[i];
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* quarter_to_half(void* ctx){
    pthread_mutex_lock(&mutex);
    for(int i = 250000; i < 500000; i++){
        sumOfArr += arr[i];
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* hafl_to_threeQuarter(void* ctx){
    pthread_mutex_lock(&mutex);
    for(int i = 500000; i < 750000; i++){
        sumOfArr += arr[i];
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* threeQuarter_to_end(void* ctx){
    pthread_mutex_lock(&mutex);
    for(int i = 750000; i < 1000000; i++){
        sumOfArr += arr[i];
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}
int main(){
    srand(time(NULL));
    for(int i = 0; i < 1000000; i++){
        arr[i] = random_number_from_1_to_100();
        sumOriginal += arr[i];
    }
    printf("Sum of array by original method: %ld\n", sumOriginal);
    pthread_t tid1, tid2, tid3, tid4;
    
    // create thread

    pthread_create(&tid1, NULL, beginning_to_quarter, NULL);
    pthread_create(&tid2, NULL, quarter_to_half, NULL);
    pthread_create(&tid3, NULL, hafl_to_threeQuarter, NULL);
    pthread_create(&tid4, NULL, threeQuarter_to_end, NULL);
    
    //join thread to thread main

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    
    printf("\nSum of array by mutil-thread: %ld\n", sumOfArr);

    return 0;
}

static int random_number_from_1_to_100() {
    return rand() % 100 + 1; // Số ngẫu nhiên từ 1 đến 10
}