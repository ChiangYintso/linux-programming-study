//
// Created by jiang on 2020/8/11.
//

#include <unistd.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    if (pid == 0) {
        /* child */
        close(fd[0]);
        char text[6] = "aa\nb\n";
        for (int i = 0; i < 26; ++i) {
            write(fd[1], text, 6);
            ++text[0];
            ++text[1];
            ++text[3];
            if (i & 1)
                sleep(5);
        }
    } else if (pid > 0) { /* parent */
        int ep_fd = epoll_create(10);
        if (ep_fd < 0) {
            perror("epoll_create error");
        }
        close(fd[1]);
        char buf[13];

        struct epoll_event evt;
        evt.events = EPOLLIN;
//        evt.events = EPOLLIN | EPOLLET;
        evt.data.fd = fd[0];
        if (epoll_ctl(ep_fd, EPOLL_CTL_ADD, fd[0], &evt) < 0) {
            perror("epoll_ctl error");

            exit(EXIT_FAILURE);
        }

        struct epoll_event ev_list[10];
        for (int i = 0; i < 26; ++i) {
            int evt_num = epoll_wait(ep_fd, ev_list, 10, -1);
            printf("evt_num: %d\n", evt_num);

            if (ev_list[0].data.fd == fd[0]) {
                int len = read(fd[0], buf, 3);
                write(STDOUT_FILENO, buf, len);
            }
        }
        close(ep_fd);
    }

    return 0;
}