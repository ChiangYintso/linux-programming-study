//
// Created by jiang on 2020/5/7.
//

#ifndef LINUX_NETWORK_ERROR_H
#define LINUX_NETWORK_ERROR_H

/**
 * Fatal error unrelated to system call,
 * print message and terminate
 * @param fmt message format
 */
_Noreturn void err_quit(const char *fmt, ...);

_Noreturn void err_sys(const char *fmt, ...);
#endif //LINUX_NETWORK_ERROR_H
