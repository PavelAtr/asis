#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

__thread int a = 5;

void* thread_function1(void* arg) {
    printf("Thread1 a=%d\n", a);
    a = 1;
    for (int i = 0; i < 10; i++) {
        printf("Thread1 a=%d\n", a);
        switchtask;
    }
    return NULL;
}

void* thread_function2(void* arg) {
    printf("Thread2 a=%d\n", a);
    a = 2;
    for (int i = 0; i < 10; i++) {
        printf("Thread2 a=%d\n", a);
        switchtask;
    }
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t thread1, thread2;

    // Create the first thread
    if (pthread_create(&thread1, NULL, thread_function1, NULL) != 0) {
        perror("Failed to create thread1\n");
        return 1;
    }

    // Create the second thread
    if (pthread_create(&thread2, NULL, thread_function2, NULL) != 0) {
        perror("Failed to create thread2\n");
        return 1;
    }

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Main thread finished\n");
    return 0;
}