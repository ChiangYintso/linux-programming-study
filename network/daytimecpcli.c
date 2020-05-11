//
// Created by jiang on 2020/5/7.
//

#include "unp.h"

int main(int argc, const char **argv) {
    int sock_fd, n;
    char recv_line[MAX_LINE + 1];
    struct sockaddr_in server_addr;

    if (argc != 2) err_quit("usage: a.out <IP address>");
    return 0;
}