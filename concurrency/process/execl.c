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

    // 进程pid, ppid没变
    char path[] = "/home/jiang/stuspace/linux_programming_study/process/cmake-build-debug/getpid";
    int result = execl(path, NULL);
    if (result == -1)
        perror("execl");
    printf("can not see me\n");
    return 0;
}
