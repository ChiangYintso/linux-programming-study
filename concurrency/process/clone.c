//
// Created by jiang on 2020/5/11.
//

#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static char msg[] = "hello";

static int child_main() {
    printf("p2: %d", getppid());
    msg[0] = 'y';
    printf(" %s\n", msg);
    exit(0);
}

int main() {
    char stack[8192];
    if (clone(&child_main,
              stack + 8192,
              CLONE_PARENT | CLONE_VFORK | CLONE_VM,
              NULL) < 0) {
        perror("clone");
        exit(EXIT_FAILURE);
    }

    printf("p1: %d %s\n", getppid(), msg);
    exit(0);
}