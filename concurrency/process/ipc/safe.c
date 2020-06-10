//
// Created by jiang on 2020/6/10.
//

#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <pthread.h>
#include<sys/mman.h>

pthread_mutex_t *get_shared_mutex(key_t key, struct shmid_ds *s) {
    key_t mt_key = shmget(key, sizeof(pthread_mutex_t), IPC_CREAT | 0600);
    pthread_mutexattr_t m_attr;
    pthread_mutex_t *mm = shmat(mt_key, NULL, 0);

    pthread_mutexattr_init(&m_attr);
    pthread_mutexattr_setpshared(&m_attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(mm, &m_attr);
    shmctl(mt_key, IPC_STAT, s);
    return mm;
}

pthread_barrier_t *get_shared_barrier() {
    pthread_barrier_t *mm = mmap(NULL, sizeof(pthread_barrier_t), PROT_READ | PROT_WRITE,
         MAP_SHARED | MAP_ANONYMOUS, -1,0);
    pthread_barrierattr_t b_attr;

    pthread_barrierattr_init(&b_attr);
//    pthread_barrierattr_setpshared(&b_attr, PTHREAD_PROCESS_SHARED);
    pthread_barrier_init(mm, &b_attr, 2);
    return mm;
}

int main() {
    key_t key;
    if ((key = shmget(454, 1023, IPC_CREAT | 0600)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    struct shmid_ds shm, shm_mt, shm_b;

    pthread_mutex_t *mutex = get_shared_mutex(123, &shm_mt);
    pthread_barrier_t *barrier = get_shared_barrier();

    int *buf = shmat(key, NULL, 0);

    shmctl(key, IPC_STAT, &shm);

//    pthread_barrier_wait(barrier);
    printf("开始\n");
    fork();
//    for (int i = 0; i < 100000; ++i) {
        pthread_mutex_lock(mutex);
        printf("hh\n");
        sleep(5);
        (*buf)++;
        pthread_mutex_unlock(mutex);
//    }

    printf("%lu\n", shm.shm_nattch);
    sleep(3);
    printf("%d\n", *buf);
    shmctl(key, IPC_RMID, &shm);
    shmctl(key, IPC_STAT, &shm);
    printf("%lu\n", shm.shm_nattch);
    shmctl(key, IPC_RMID, &shm_mt);
    shmctl(key, IPC_RMID, &shm_b);
    munmap(barrier, sizeof(*barrier));
    return 0;
}