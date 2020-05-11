//
// Created by jiang on 2020/5/11.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char buf[] = "hello";
    pid_t pid = vfork();
    if (pid == 0) {
        buf[2] = 'a';
        printf("child pid: %d\n", getpid());
    } else if (pid < 0) {
        perror("vfork");
    } else {
        printf("father pid: %d\n", getpid());
    }

    printf("%d: %s\n", getpid(), buf);
    exit(0);
}