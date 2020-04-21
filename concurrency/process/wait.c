//
// Created by jiang on 2020/4/20.
//

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int status;
    pid_t pid;
    if (!fork()) {
        printf("child pid: %d\n", getpid());
        return 1;
    }

    pid = wait(&status);
    if (pid == -1) {
        perror("wait");
    }

    printf("child pid: %d\n", pid);
    if (WIFEXITED(status)) {
        printf("Normal termination with exit status=%d\n", WEXITSTATUS(status));
    }
    printf("status: %d\n", status);
    return 0;
}