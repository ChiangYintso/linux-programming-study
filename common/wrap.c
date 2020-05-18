//
// Created by jiang on 2020/5/13.
//
#include "unp.h"
#include <unistd.h>
#include "common/error.h"

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

void Write(int fd, void *buf, int n) {
    if (write(fd, buf, n) != n)
        err_sys("write");
}

void Lseek(int fd, __off_t offset, int whence) {
    if ((lseek(fd, offset, whence)) == -1)
        err_sys("lseek error");
}
