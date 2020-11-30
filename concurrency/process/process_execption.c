//
// Created by jiang on 2020/11/30.
//

#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        puts("child process");
        sleep(1);
        for (int i = 10; i > -10; --i) {
            printf("%d\n", 20 / i);
            sleep(1);
        }
    } else {
        printf("%d\n", pid);
        for (int i = 0; i < 10; ++i) {
            puts("go on");
            sleep(4);
        }
    }
    return 0;
}