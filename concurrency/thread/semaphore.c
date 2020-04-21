//
// Created by jiang on 2020/4/20.
//

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static sem_t text_sem;

#define WORK_SIZE 1024
static char work_area[WORK_SIZE];

void output_sem_val(sem_t *sem) {
    int sem_val;
    if (sem_getvalue(sem, &sem_val) != 0) {
        perror("sem_getvalue");
        exit(EXIT_FAILURE);
    }
    printf("sem_val: %d\n", sem_val);
}

static void *thread_func(void *args) {
    int *tid = (int *) args;
    printf("thread %d started\n", *tid);
    sem_wait(&text_sem);
    while (strncmp("end", work_area, 3) != 0) {
        printf("thread %d: You input %lu characters\n", *tid, strlen(work_area) - 1);
        sem_wait(&text_sem);
    }
    return args;
}

int main() {
    output_sem_val(&text_sem);
#define THREAD_COUNT 10
    pthread_t thread[THREAD_COUNT];
    if (sem_init(&text_sem, 0, 0) != 0) {
        perror("sem_init");
        exit(EXIT_FAILURE);
    }
    int thread_num[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < THREAD_COUNT; ++i) {
        if (pthread_create(&thread[i], NULL, thread_func, (void *) (thread_num + i)) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    printf("Input some text, Enter `end` to finish...\n");
    while (1) {
        fgets(work_area, WORK_SIZE, stdin);
        if (strncmp("end", work_area, 3) == 0) break;
        sem_post(&text_sem);
        output_sem_val(&text_sem);
    }
    output_sem_val(&text_sem);
    void *thread_result;
    printf("Waiting for thread to finish...\n");
    for (int i = 0; i < THREAD_COUNT; ++i)
        sem_post(&text_sem);
    for (int i = 0; i < THREAD_COUNT; ++i) {
        if (pthread_join(thread[i], &thread_result) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
        printf("Thread %d joined\n", *(int *)thread_result);
    }

    output_sem_val(&text_sem);
    sem_destroy(&text_sem);
    return 0;
}