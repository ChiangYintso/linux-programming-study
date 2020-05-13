//
// Created by jiang on 2020/5/13.
//
#include "unp.h"
#include "tcp_cli.h"
#include <string.h>
#include "utils/error.h"

int tcp_cli(const char * ip_addr, int port) {
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
    server_addr.sin_port = htons(port);

    // 将字符串形式的ip地址转换成一个uint32_t
    if (inet_pton(AF_INET, ip_addr, &server_addr.sin_addr) <= 0)
        err_quit("inet_pton error for %s", ip_addr);

    // 建立一个TCP连接
    if (connect(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        err_sys("connect error");
    return sock_fd;
}