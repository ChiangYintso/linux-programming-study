//
// Created by jiang on 2020/5/17.
//

#include <zconf.h>
#include <stdio.h>
#include <fcntl.h>

char buf[500000];

int main() {
    int n_to_write, n_write;
    set_fl(STDOUT_FILENO, O_NONBLOCK);
    n_to_write = read(STDIN_FILENO, buf, sizeof(buf));

    fprintf(stderr, "read %d bytes\n", n_to_write);
    return 0;
}