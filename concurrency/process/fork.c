//
// Created by jiang on 2020/4/20.
//

#include <unistd.h>
#include <stdio.h>

int main() {
    char hello[] = "hello";
    printf("start\n");
    pid_t pid;
    pid = fork();
    if (pid > 0) {
        printf("%s\n", hello);
        printf("I am the parent of pid %d, I am %d\n", pid, getpid());
    } else if (!pid) {
        printf("%s\n", hello);
        printf("I am the child of pid %d, I am %d\n", getppid(), getpid());
    } else if (pid == -1) {
        perror("fork");
    }
    printf("bye\n");
    return 0;
}