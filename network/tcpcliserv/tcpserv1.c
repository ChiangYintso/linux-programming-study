//
// Created by jiang on 2020/7/26.
//

#include "../wrap.h"
#include "../unp.h"
#include "../err_handle.h"
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h>
#include "sig_child_wait.h"

static void str_echo(int sock_fd, const char *addr, uint16_t client_port) {
    ssize_t n;
    char buf[MAXLINE + 1];
    while ((n = read(sock_fd, buf, MAXLINE)) > 0) {
        buf[n] = '\0';
        Write(sock_fd, buf, strlen(buf));
        printf("received: %s", buf);
    }
    if (n < 0) {
        err_exit("str_echo");
    } else {
        printf("client %s:%d EOF.\n", addr, client_port);
    }
}

int main(int argc, char *argv[]) {
    int listen_fd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERVER_PORT);

    Bind(listen_fd, (const struct sockaddr *) &serv_addr, sizeof(serv_addr));
    Listen(listen_fd, LISTENQ);

    // fork child process must handle SIGCHLD
    if (signal(SIGCHLD, sig_child_wait) == SIG_ERR) {
        perror("signal error");
        exit(EXIT_FAILURE);
    }

    int conn_fd;

    struct sockaddr_in cli_addr;
    socklen_t conn_socklen = sizeof(cli_addr);

    char addr[20];
    printf("start listening at %s:%d\n", inet_ntop(AF_INET, (void *) &serv_addr.sin_addr, addr, INET_ADDRSTRLEN),
           SERVER_PORT);
    uint16_t client_port;
    for (;;) {
        conn_fd = Accept(listen_fd, (struct sockaddr *) &cli_addr, &conn_socklen);
        client_port = ntohs(cli_addr.sin_port);
        printf("connected from %s:%d\n", inet_ntop(AF_INET, (void *) &cli_addr.sin_addr, addr, INET_ADDRSTRLEN),
               client_port);
        if (fork() == 0) {
            Close(listen_fd);
            str_echo(conn_fd, addr, client_port);
            exit(EXIT_SUCCESS);
        }
        Close(conn_fd);
    }
}