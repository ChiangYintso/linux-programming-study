//
// Created by jiang on 2020/6/10.
//

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <zconf.h>
#include <stdlib.h>

int main() {
    key_t key;
    if ((key = shmget(123, 0, IPC_CREAT)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    char *buf = (char *) shmat(key, NULL, 0);
    for (int i = 0; i < 3; ++i) {
        printf("%s\n", buf);
        sleep(5);
    }
    return 0;
}