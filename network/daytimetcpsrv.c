//
// Created by jiang on 2020/7/26.
//

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "unp.h"
#include "wrap.h"

int main(int argc, char *argv[]) {
    int listen_fd;

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);


    listen_fd = Socket(AF_INET, SOCK_STREAM, 0);
    Bind(listen_fd, (const struct sockaddr *) &servaddr, sizeof(servaddr));

    Listen(listen_fd, LISTENQ);

    char buffer[MAXLINE];
    time_t ticks;
    int conn_fd;

    char addr[20];
    inet_ntop(AF_INET, (void *) &servaddr.sin_addr, addr, INET_ADDRSTRLEN);
    printf("start listening at %s:%d\n", addr, SERVER_PORT);

    struct sockaddr_in conn_sockaddr;
    socklen_t conn_socklen = sizeof(conn_sockaddr);
    for (;;) {
        conn_fd = Accept(listen_fd, (struct sockaddr *) &conn_sockaddr, &conn_socklen);
        printf("connected from %s:%d\n", inet_ntop(AF_INET, (void *) &conn_sockaddr.sin_addr, addr, INET_ADDRSTRLEN),
               ntohs(conn_sockaddr.sin_port));
        ticks = time(NULL);
        snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&ticks));
        Write(conn_fd, buffer, sizeof(buffer));
        Close(conn_fd);
    }
}