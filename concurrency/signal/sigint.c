//
// Created by jiang on 2020/5/11.
//

#include <signal.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <unistd.h>

struct winsize sz;

static void sigwinch_handler(int sig) {
    static int count = 0;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &sz);
    printf("%d: %u列 %u行\n", ++count, sz.ws_col, sz.ws_row);
}

static void sigint_handler(int sig) {
    printf("sig %d: CTRL+C\n", sig);
}

int main(int argc, char **argv) {
    printf("pid: %d\n", getpid());
    if (signal(SIGWINCH, sigwinch_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }
    getchar();
    exit(EXIT_SUCCESS);
}
