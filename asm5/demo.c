#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_BUFFER 256

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_input = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_write = PTHREAD_COND_INITIALIZER;

char buffer[MAX_BUFFER];
int data_ready = 0;  // Biến trạng thái để báo hiệu dữ liệu sẵn sàng

// Thread 1: Nhập dữ liệu từ bàn phím
void *input_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        
        // Nhập dữ liệu
        printf("Nhap thong tin sinh vien (Ho ten, ngay sinh, que quan): ");
        fgets(buffer, MAX_BUFFER, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Xóa ký tự xuống dòng
        
        data_ready = 1; // Báo hiệu dữ liệu đã sẵn sàng
        pthread_cond_signal(&cond_write); // Thông báo cho thread ghi
        
        // Chờ thread 3 báo hiệu để tiếp tục nhập dữ liệu
        pthread_cond_wait(&cond_input, &mutex);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Thread 2: Ghi dữ liệu vào file
void *write_thread(void *arg) {
    FILE *file;
    while (1) {
        pthread_mutex_lock(&mutex);
        
        while (!data_ready) {
            pthread_cond_wait(&cond_write, &mutex); // Chờ dữ liệu từ thread 1
        }
        
        // Mở file để ghi
        file = fopen("thongtinsinhvien.txt", "a");
        if (file == NULL) {
            perror("Loi mo file");
            pthread_mutex_unlock(&mutex);
            exit(1);
        }
        fprintf(file, "%s\n", buffer); // Ghi dữ liệu vào file
        fclose(file);
        
        data_ready = 0; // Đặt lại trạng thái
        pthread_cond_signal(&cond_input); // Thông báo cho thread 1 tiếp tục
        
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Thread 3: Đọc dữ liệu từ file và in ra terminal
void *read_thread(void *arg) {
    FILE *file;
    char line[MAX_BUFFER];
    while (1) {
        sleep(1); // Tạo độ trễ để file có dữ liệu mới
        pthread_mutex_lock(&mutex);
        
        // Đọc dữ liệu từ file
        printf("Noi dung file thongtinsinhvien.txt:\n");
        file = fopen("thongtinsinhvien.txt", "r");
        if (file == NULL) {
            perror("Loi mo file");
            pthread_mutex_unlock(&mutex);
            exit(1);
        }
        
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line); // In từng dòng từ file
        }
        printf("\n");
        fclose(file);
        
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2, tid3;
    
    // Tạo các thread
    pthread_create(&tid1, NULL, input_thread, NULL);
    pthread_create(&tid2, NULL, write_thread, NULL);
    pthread_create(&tid3, NULL, read_thread, NULL);
    
    // Chờ các thread kết thúc
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    
    return 0;
}
