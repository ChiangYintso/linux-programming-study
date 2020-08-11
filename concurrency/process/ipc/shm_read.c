//
// Created by jiang on 2020/6/10.
//

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <zconf.h>

int main() {
    key_t key;
    usleep(100);

    // 打开共享内存
    if ((key = shmget(888, 0, IPC_CREAT)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // 获取指针
    int *buf = shmat(key, NULL, 0);

    // 读写锁信号量
    sem_t *rw_mutex = sem_open("share", O_RDWR | O_CREAT, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH), 1);

    usleep(100);
    for (int i = 0; i < 10; ++i) {
        sem_wait(rw_mutex);
        printf("%d\n", buf[0]);
        sem_post(rw_mutex);
    }
    sleep(1);
    sem_wait(rw_mutex);
    printf("read: %d\n", buf[0]);
    sem_post(rw_mutex);
    shmdt(buf);
    return 0;
}