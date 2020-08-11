//
// Created by jiang on 2020/7/26.
//

#include "err_handle.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

_Noreturn void err_exit(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int err = errno;
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ": %s\n", strerror(err));
    va_end(ap);
    exit(EXIT_FAILURE);
}