#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "unp.h"
#include "wrap.h"
#include "err_handle.h"

int main(int argc, char *argv[]) {
    if (argc != 2)
        fputs("usage: daytimetcpcli <IPaddress>", stderr);

    int sock_fd = Socket(AF_INET6, SOCK_STREAM, 0);

    struct sockaddr_in6 servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin6_family = AF_INET6;
    servaddr.sin6_port = htons(SERVER_PORT); // daytime server
    if (inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0) {
        err_exit("inet_pton error for %s", argv[1]);
    }

    if (connect(sock_fd, (const struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        err_exit("connect error");
    }

    int n;
    char recvline[MAXLINE + 1];
    while ((n = read(sock_fd, recvline, MAXLINE)) > 0) {
        recvline[n] = '\0';
        if (fputs(recvline, stdout) == EOF)
            fprintf(stderr, "EOF\n");
    }
    if (n < 0)
        err_exit("read error");
    return 0;
}
