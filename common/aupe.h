//
// Created by jiang on 2020/5/14.
//

#ifndef IO_AUPE_H
#define IO_AUPE_H

#include <fcntl.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

void set_fl(int fd, int flags); /* flags are file status flags to turn on */

void clr_fl(int fd, int flags);
#endif //IO_AUPE_H
