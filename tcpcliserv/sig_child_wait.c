//
// Created by jiang on 2020/8/9.
//

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include "sig_child_wait.h"

void sig_child_wait(int signo) {
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
        printf("child %d terminated\n", pid);
    }
}