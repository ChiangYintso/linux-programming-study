//
// Created by jiang on 2020/8/9.
//
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../unp.h"
#include "../wrap.h"

int main(int argc, char *argv[]) {
    int listen_fd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERVER_PORT);

    Bind(listen_fd, (const struct sockaddr *) &serv_addr, sizeof(serv_addr));
    Listen(listen_fd, LISTENQ);

    int max_fd = listen_fd;
    int client[FD_SETSIZE], max_cli_i = -1;
    memset(client, -1, sizeof(client));

    fd_set all_set;
    FD_ZERO(&all_set);
    FD_SET(listen_fd, &all_set);

    char addr[20];
    printf("start listening at %s:%d\n", inet_ntop(AF_INET, (void *) &serv_addr.sin_addr, addr, INET_ADDRSTRLEN),
           SERVER_PORT);

    char buf[MAXLINE];

    for (;;) {
        fd_set read_set = all_set;
        int n_ready = Select(max_fd + 1, &read_set, NULL, NULL, NULL);

        if (FD_ISSET(listen_fd, &read_set)) {

            /* new client connection */
            struct sockaddr_in cli_addr;
            socklen_t conn_socklen = sizeof(cli_addr);

            int conn_fd = Accept(listen_fd, (struct sockaddr *)&cli_addr, &conn_socklen);

            int i;
            for (i = 0; i < FD_SETSIZE; ++i) {
                if (client[i] == -1) {
                    /* save fd */
                    client[i] = conn_fd;
                    uint16_t client_port = ntohs(cli_addr.sin_port);
                    printf("connected from %s:%d\n", inet_ntop(AF_INET, (void *) &cli_addr.sin_addr, addr, INET_ADDRSTRLEN),
                           client_port);
                    break;
                }
            }
            if (i == FD_SETSIZE) {
                perror("too many clients");
            }

            /* add new fd to set */
            FD_SET(conn_fd, &all_set);

            if (conn_fd > max_fd) max_fd = conn_fd;
            if (i > max_cli_i) max_cli_i = i;

            /* no more readable fd */
            if (--n_ready <= 0) continue;
        }

        int sock_fd;
        for (int i = 0; i <= max_cli_i; ++i) {
            /* check all clients for data */
            if ((sock_fd = client[i]) < 0) continue;
            if (FD_ISSET(sock_fd, &read_set)) {
                int n;
                if ((n = read(sock_fd, buf, MAXLINE)) == 0) {
                    Close(sock_fd);
                    puts("client disconnected");
                    FD_CLR(sock_fd, &all_set);
                    client[i] = -1;
                } else {
                    write(sock_fd, buf, n);
                }

                /* no more readable descriptors */
                if (--n_ready <= 0)
                    break;
            }
        }
    }
}