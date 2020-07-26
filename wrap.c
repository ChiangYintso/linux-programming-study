//
// Created by jiang on 2020/7/26.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "sys/socket.h"
#include "wrap.h"
#include "err_handle.h"

int Socket(int domain, int type, int protocol) {
    int fd;
    if ((fd = socket(domain, type, protocol)) < 0) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }
    return fd;
}

void Bind(int fd, const struct sockaddr *addr, socklen_t len) {
    if (bind(fd, addr, len) < 0) {
        perror("bind error");
        exit(EXIT_FAILURE);
    }

}

void Listen(int fd, int n) {
    if (listen(fd, n) < 0) {
        perror("listen error");
        exit(EXIT_FAILURE);
    }

}

int Accept(int fd, struct sockaddr *__restrict addr,
           socklen_t *__restrict addr_len) {
    int conn_fd;
    if ((conn_fd = accept(fd, addr, addr_len)) < 0) {
        perror("accept error");
        exit(EXIT_FAILURE);
    }

    return conn_fd;
}

int Write(int fd, const void *buffer, size_t n) {
    int write_n;
    if ((write_n = write(fd, buffer, n)) < 0) {
        perror("write error");
        exit(EXIT_FAILURE);
    }
    return write_n;
}

void Close(int fd) {
    if (close(fd) < 0) {
        perror("close error");
        exit(EXIT_FAILURE);
    }
}

void Inet_pton(int af, const char *__restrict cp,
               void *__restrict buf) {
    if (inet_pton(af, cp, buf) <= 0) {
        err_exit("inet_pton error for %s", cp);
    }
}

void Connect(int sock_fd, const struct sockaddr *servaddr, socklen_t socklen) {
    if (connect(sock_fd, servaddr, socklen) < 0) {
        err_exit("connect error");
    }
}