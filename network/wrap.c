//
// Created by jiang on 2020/5/13.
//
#include "unp.h"
#include "unistd.h"
#include "utils/error.h"

void Close(int fd) {
    if (close(fd) == -1)
        err_sys("close error");
}

pid_t Fork() {
    pid_t pid;
    if ((pid = fork()) == -1)
        err_sys("fork error");
    return pid;
}