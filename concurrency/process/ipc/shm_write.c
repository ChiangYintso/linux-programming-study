//
// Created by jiang on 2020/5/22.
//

#include <sys/shm.h>
#include <string.h>
#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include <wait.h>

int main() {
    key_t key;

    // 打开共享内存
    if ((key = shmget(888, sizeof(int), IPC_CREAT | 0600)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_t write_lock;
    pthread_mutexattr_t wr_attr;

    pthread_mutexattr_init(&wr_attr);
    pthread_mutexattr_setpshared(&wr_attr, PTHREAD_PROCESS_SHARED);

    // 写锁
    pthread_mutex_init(&write_lock, &wr_attr);

    // 读写锁信号量
    sem_t *rw_mutex = sem_open("share", O_RDWR | O_CREAT, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH), 1);
    int *buf = shmat(key, NULL, 0);
    buf[0] = 0;
    struct shmid_ds shm;

    shmctl(key, IPC_STAT, &shm);
    pid_t pid = fork();

    for (int i = 0; i < 1000000; ++i) {
        pthread_mutex_lock(&write_lock);
        sem_wait(rw_mutex);
        buf[0] += 2;
        sem_post(rw_mutex);
        pthread_mutex_unlock(&write_lock);
    }

    int stat;
    wait(&stat);
    if (pid != 0) {
        printf("write %d\n", buf[0]);
        shmctl(key, IPC_RMID, &shm);
    }

    return 0;
}