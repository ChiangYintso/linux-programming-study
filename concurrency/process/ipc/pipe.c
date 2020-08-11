//
// Created by jiang on 2020/8/11.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    int fd[2];

    if (pipe(fd) < 0) {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    int pid;
    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid > 0) { /* parent */
        close(fd[0]);
        write(fd[1], "hello world\n", 12);
    } else {
        close(fd[1]);
        char line[1024];
        n = read(fd[0], line, 1024);
        write(STDOUT_FILENO, line, n);
    }
    return 0;
}