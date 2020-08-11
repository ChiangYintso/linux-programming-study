//
// Created by jiang on 2020/5/7.
//

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <stdbool.h>
#include <stdlib.h>
#include "error.h"
#include "unp.h"

int daemon_proc;

static void err_do(_Bool errno_flag, int level, const char *fmt, va_list ap) {
    int errno_save, n;
    char buf[MAX_LINE + 1];
    errno_save = errno;
    vsnprintf(buf, MAX_LINE, fmt, ap);

    n = (int) strlen(buf);
    if (errno_flag)
        snprintf(buf + n, MAX_LINE - n, ": %s", strerror(errno_save));
    strcat(buf, "\n");

    if (daemon_proc)
        syslog(level, "%s", buf);
    else {
        fflush(stdout);
        fputs(buf, stderr);
        fflush(stderr);
    }
}

_Noreturn void err_quit(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_do(false, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(EXIT_FAILURE);
}

_Noreturn void err_sys(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    err_do(true, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(EXIT_FAILURE);
}
