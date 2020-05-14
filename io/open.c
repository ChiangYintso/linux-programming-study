//
// Created by jiang on 2020/5/14.
//

#include <unistd.h>
#include <fcntl.h>
#include "aupe.h"
#include "utils/error.h"

int main() {
    int fd = open("hello.txt", O_RDWR|O_CREAT, FILE_MODE);
    if (write(fd, "hello world", 11) != 11)
        err_sys("write");
    if ((lseek(fd, 0100, SEEK_SET)) == -1)
        err_sys("lseek error");
    if (write(fd, "bye", 3) != 3)
        err_sys("write");

    return 0;
}