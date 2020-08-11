#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include "unp.h"
#include "wrap.h"
#include "err_handle.h"

int main(int argc, char *argv[]) {
    if (argc != 2)
        fputs("usage: daytimetcpcli <IPaddress>", stderr);

    int sock_fd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT); // daytime server

    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    Connect(sock_fd, (const struct sockaddr *) &servaddr, sizeof(servaddr));

    int n;
    char recvline[MAXLINE + 1];
    while ((n = read(sock_fd, recvline, MAXLINE)) > 0) {
        recvline[n] = '\0';
        if (fputs(recvline, stdout) == EOF)
            fprintf(stderr, "EOF\n");
    }
    Close(sock_fd);
    if (n < 0)
        err_exit("read error");
    return 0;
}
