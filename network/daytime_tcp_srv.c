//
// Created by jiang on 2020/5/12.
//

#include "common/unp.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <zconf.h>
#include <stdlib.h>
#include "utils/error.h"

int main(int argc, char *argv[]) {
    int listen_fd, conn_fd;
    struct sockaddr_in server_addr;
    char buff[MAX_LINE];
    time_t ticks;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(9999);

    bind(listen_fd, (const struct sockaddr *) &server_addr, sizeof(server_addr));
    listen(listen_fd, LISTENQ);

    pid_t pid;
    for(;;) {
        if ((conn_fd = accept(listen_fd, NULL, NULL)) == -1)
            err_quit("accept error");

        if ((pid = Fork()) == 0) {
            Close(listen_fd);
            for (int i = 1; i <= 15; ++i) {
                sleep(1);
                snprintf(buff, sizeof(buff), "%d\r\n", i);
                write(conn_fd, buff, strlen(buff));
            }
            ticks = time(NULL);
            snprintf(buff, sizeof(buff), "%.23s\r\n", ctime(&ticks));
            write(conn_fd, buff, strlen(buff));
            Close(conn_fd);
            exit(0);
        }
        Close(conn_fd);
    }
}