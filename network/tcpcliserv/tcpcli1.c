//
// Created by jiang on 2020/7/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "../wrap.h"
#include "../unp.h"
#include "../writen.h"

void str_cli(int sock_fd) {
    char send_line[MAXLINE], recv_line[MAXLINE];
    ssize_t n;
    while ((n = read(STDIN_FILENO, send_line, MAXLINE)) > 0) {
        send_line[n] = '\0';
        if (writen(sock_fd, send_line, n) < 0) {
            perror("writen error");
            exit(EXIT_FAILURE);
        }
        if ((n = read(sock_fd, recv_line, MAXLINE)) < 0) {
            fputs("str_cli: server terminated prematurely", stderr);
            exit(EXIT_FAILURE);
        }
        recv_line[n] = '\0';
        fputs(recv_line, stdout);
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

    str_cli(sock_fd);
    return 0;
}