//
// Created by jiang on 2020/7/26.
//

#ifndef UNP_STUDY_WRAP_H
#define UNP_STUDY_WRAP_H

#include <sys/socket.h>
#include <sys/poll.h>

int Socket(int domain, int type, int protocol);

void Bind(int fd, const struct sockaddr *addr, socklen_t len);

void Listen(int fd, int n);

int Accept(int fd, struct sockaddr *__restrict addr,
           socklen_t *__restrict addr_len);

int Write(int fd, const void *buffer, size_t n);

void Close(int fd);

void Inet_pton(int af, const char *__restrict cp,
               void *__restrict buf);

void Connect(int sock_fd, const struct sockaddr *servaddr, socklen_t socklen);

void Shutdown(int sock_fd, int how);

int Select(int maxfdp1, fd_set *__restrict readfds,
           fd_set *__restrict writefds,
           fd_set *__restrict exceptfds,
           struct timeval *__restrict timeout);

int Poll(struct pollfd *__fds, nfds_t __nfds, int __timeout);

#endif //UNP_STUDY_WRAP_H
