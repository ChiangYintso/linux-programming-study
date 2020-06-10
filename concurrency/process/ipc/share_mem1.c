//
// Created by jiang on 2020/5/22.
//

#include <sys/shm.h>
#include <string.h>
#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    key_t key;
    if ((key = shmget(454, 1023, IPC_CREAT | 0600)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    char *buf = (char *) shmat(key, NULL, 0);
    for (int i = 0; i < 26; ++i) {
        strcpy(buf, "  hello world");
        buf[0] = 'A' + i;
        sleep(5);
    }

    return 0;
}