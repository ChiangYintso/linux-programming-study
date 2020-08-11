//
// Created by jiang on 2020/4/21.
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THREADS_COUNT 10

pthread_mutex_t mutex;
int count = 0;

void *thread_func(void *args) {
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);
        count++;
        printf("%lu\n", pthread_self());
        pthread_mutex_unlock(&mutex);
    }
    return args;
}

int main() {
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("pthread_mutex_init");
        exit(EXIT_FAILURE);
    }

    pthread_t threads[THREADS_COUNT];
    for (int i = 0; i < THREADS_COUNT; ++i) {
        if (pthread_create(&threads[i], NULL, thread_func, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    void *res;
    for (int i = 0; i < THREADS_COUNT; ++i) {
        pthread_join(threads[i], &res);
    }
    printf("%d\n", count);
    return 0;
}