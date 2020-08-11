//
// Created by jiang on 2020/8/9.
//

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <string.h>
#include <netinet/in.h>
#include "../unp.h"
#include "../wrap.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

void str_cli(FILE *fp, int sock_fd) {
    fd_set read_set;
    FD_ZERO(&read_set);

    _Bool stdin_eof = false;
    char sendline[MAXLINE], recv_line[MAXLINE];

    for (;;) {
        if (!stdin_eof) {
            FD_SET(fileno(fp), &read_set);
        }
        FD_SET(sock_fd, &read_set);
        int maxfdp1 = max(fileno(fp), sock_fd) + 1;
        Select(maxfdp1, &read_set, NULL, NULL, NULL);

        int n;
        if (FD_ISSET(sock_fd, &read_set)) {
            /* socket is readable */
            if ((n = read(sock_fd, recv_line, MAXLINE)) <= 0) {
                if (n == 0 && stdin_eof) {
                    fputs("bye~", stdout);
                    return;
                }
                fputs("str_cli: server terminated prematurely", stderr);
                exit(EXIT_FAILURE);
            }
            recv_line[n] = '\0';
            fputs(recv_line, stdout);
        }
        if (FD_ISSET(fileno(fp), &read_set)) {
            /* input is readable */
            if ((n = read(fileno(fp), sendline, MAXLINE)) == 0) {
                stdin_eof = true;
                Shutdown(sock_fd, SHUT_WR);
                FD_CLR(sock_fd, &read_set);
                continue;
            }
            sendline[n] = '\0';
            write(sock_fd, sendline, n);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: tcpcli1 <IPAddress>\n");
        exit(EXIT_FAILURE);
    }
    int sock_fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    Inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    Connect(sock_fd, (const struct sockaddr *) &server_addr, sizeof(server_addr));

    str_cli(stdin, sock_fd);
    return 0;
}