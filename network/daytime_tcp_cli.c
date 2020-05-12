//
// Created by jiang on 2020/5/7.
//
#include <string.h>
#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include "unp.h"
#include "utils/error.h"

int main(int argc, const char *argv[]) {
    if (argc != 2) err_quit("usage: <file name> <IP address>");

    // socket file descriptor(socket 文件描述符)
    int sock_fd;

    // IPv4协议、TCP连接
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

    struct sockaddr_in server_addr;
    // 结构体清零
    bzero(&server_addr, sizeof(server_addr));

    // 指定IPv4协议
    server_addr.sin_family = AF_INET;
    // 指定端口号
    server_addr.sin_port = htons(9999);

    // 将字符串形式的ip地址转换成一个uint32_t
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0)
        err_quit("inet_pton error for %s", argv[1]);

    // 建立一个TCP连接
    if (connect(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        err_sys("connect error");

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