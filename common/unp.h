//
// Created by jiang on 2020/5/7.
//

#ifndef LINUX_NETWORK_UNP_H
#define LINUX_NETWORK_UNP_H

#include <netinet/in.h>
#include <arpa/inet.h>

#define LISTENQ 1024 // 2nd argument to listen()
#define MAX_LINE 4096 // max text line length

void Close(int fd);

pid_t Fork();

void Write(int fd, void *buf, int n);

void Lseek(int fd, __off_t offset, int whence);

#endif //LINUX_NETWORK_UNP_H
