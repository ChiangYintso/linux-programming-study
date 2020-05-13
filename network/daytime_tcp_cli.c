//
// Created by jiang on 2020/5/7.
//
#include <string.h>
#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include "unp.h"
#include "utils/error.h"
#include "tcp_cli.h"

int main(int argc, const char *argv[]) {
    if (argc != 2) err_quit("usage: <file name> <IP address>");

    int sock_fd = tcp_cli(argv[1], 9999);

    // 读取服务器的response
    int n;
    char recv_line[MAX_LINE + 1];
    while ((n = read(sock_fd, recv_line, MAX_LINE)) > 0) {
        recv_line[n] = 0;
        if (fputs(recv_line, stdout) == EOF)
            err_sys("fputs error");
    }
    if (n < 0)
        err_sys("read error");
    exit(0);
}