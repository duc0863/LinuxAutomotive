#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

//global variables
static int random_number_from_1_to_100();
static int arr[100];
int countOdd = 0;
int countEven = 0;


void* CountEvenNumbers(void* ctx){
    
    for(int i = 0; i < 100; i++){
        if(!(arr[i]&1))
            countEven++;
    }
    
    return NULL;
}

void* CountOddNumbers(void* ctx){

    for(int i = 0; i < 100; i++){
        if(arr[i]&1)
            countOdd++;
    }
    
    return NULL;
}

int main(){
    srand(time(NULL));
    for(int i = 0; i < 100; i++){
        arr[i] = random_number_from_1_to_100();
        printf("%d ", arr[i]);
    }
    pthread_t tid1, tid2;
    
    // create thread

    pthread_create(&tid1, NULL, CountEvenNumbers, NULL);
    pthread_create(&tid2, NULL, CountOddNumbers, NULL);
    
    //join thread to thread main

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("\nNumber of even number: %d\n", countEven);
    printf("\nNumber of odd number: %d\n", countOdd);

    return 0;
}

static int random_number_from_1_to_100() {
    return rand() % 100 + 1; // Số ngẫu nhiên từ 1 đến 10
}