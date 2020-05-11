//
// Created by jiang on 2020/5/7.
//

#include <stdio.h>
#include <stdarg.h>
#include "error.h"

static void err_doit(int errno_flag, int level, const char *fmt, va_list ap) {

}

void err_sys(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);

}
