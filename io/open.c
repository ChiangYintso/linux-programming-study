//
// Created by jiang on 2020/5/14.
//

#include <unistd.h>
#include <fcntl.h>
#include <common/unp.h>
#include <stdio.h>
#include "common/aupe.h"
#include "common/error.h"

int main() {
    int fd = open("hello.txt", O_RDWR | O_CREAT | O_TRUNC, FILE_MODE);
    Lseek(fd, 020, SEEK_SET);
    Write(fd, "qqqq", 4);

    Lseek(fd, 05, SEEK_SET);
    Write(fd, "xxxx", 4);

    Lseek(fd, 0, SEEK_SET);
    int n;
    char buf[MAX_LINE + 1];
    while ((n = read(fd, buf, MAX_LINE)) > 0) {
        buf[n] = 0;
        Write(STDOUT_FILENO, buf, n + 1);
        if (fputs(buf, stdout) == EOF)
            err_sys("fputs error");
    }
    if (n < 0)
        err_sys("read error");
    return 0;
}