//
// Created by jiang on 2020/4/20.
//
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = getpid();
    pid_t ppid = getppid();
    printf("My pid: %d\n", pid);
    printf("Parent's pid: %d\n", ppid);
    return 0;
}

