//
// Created by jiang on 2020/7/26.
//

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "writen.h"

ssize_t writen(int fd, const void *vptr, size_t n) {
    size_t n_left = n;
    const char *ptr = vptr;

    size_t n_writen;
    while (n_left > 0) {
        if ((n_writen = write(fd, ptr, n_left)) <= 0) {
            if (n_writen < 0 && errno == EINTR)
                n_writen = 0;
            else
                return -1; // error
        }
        n_left -= n_writen;
        ptr += n_writen;
    }
    return n;
}
