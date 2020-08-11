//
// Created by jiang on 2020/8/9.
//

#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "../wrap.h"
#include "../unp.h"

#define INFTIM -1
#define OPEN_MAX 1024

int main(int argc, char *argv[]) {
    int listen_fd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERVER_PORT);

    Bind(listen_fd, (const struct sockaddr *) &serv_addr, sizeof(serv_addr));
    Listen(listen_fd, LISTENQ);

    struct pollfd client[OPEN_MAX];
    client[0].fd = listen_fd;
    client[0].events = POLLRDNORM;
    for (int i = 1; i < OPEN_MAX; ++i) {
        client[i].fd = -1;
    }

    char addr[20];
    printf("start listening at %s:%d\n", inet_ntop(AF_INET, (void *) &serv_addr.sin_addr, addr, INET_ADDRSTRLEN),
           SERVER_PORT);

    int max_cli_i = 0;

    char buf[MAXLINE];
    for (;;) {
        int n_ready = Poll(client, max_cli_i + 1, INFTIM);

        if (client[0].revents & POLLRDNORM) {
            /* new client connection */
            struct sockaddr_in cli_addr;
            socklen_t conn_socklen = sizeof(cli_addr);
            int conn_fd = Accept(listen_fd, (struct sockaddr *) &cli_addr, &conn_socklen);

            int i;
            for (i = 1; i < OPEN_MAX; ++i) {
                if (client[i].fd < 0) {
                    client[i].fd = conn_fd;
                    uint16_t client_port = ntohs(cli_addr.sin_port);
                    printf("connected from %s:%d\n", inet_ntop(AF_INET, (void *) &cli_addr.sin_addr, addr, INET_ADDRSTRLEN),
                           client_port);
                    break;
                }
            }
            if (i == FD_SETSIZE) {
                fputs("too many clients", stderr);
            }
            client[i].events = POLLRDNORM;

            if (i > max_cli_i) max_cli_i = i; /* max index in client[] array */
            if (--n_ready <= 0)
                continue;  /* no more readable descriptors */
        }

        int sock_fd;
        for (int i = 1; i <= max_cli_i; ++i) {
            /* check all clients for data */
            if ((sock_fd = client[i].fd) < 0)
                continue;
            if (client[i].revents & (POLLRDNORM | POLLERR)) {
                int n;
                if ((n = read(sock_fd, buf, MAXLINE)) < 0) {
                    if (errno == ECONNRESET) {
                        /* connection reset by client */
                        Close(sock_fd);
                        client[i].fd = -1;
                        puts("client reset");
                    } else {
                        fputs("error", stderr);
                    }
                } else if (n == 0) {
                    /* connection closed by client */
                    Close(sock_fd);
                    puts("client disconnected");
                    client[i].fd = -1;
                } else {
                    Write(sock_fd, buf, n);
                }
                if (--n_ready <= 0) break;
            }
        }
    }

}