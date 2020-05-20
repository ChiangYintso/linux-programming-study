//
// Created by jiang on 2020/5/13.
//

#include <stdio.h>
#include <stdint.h>

int main() {
    union {
        int16_t a;
        char b[sizeof(int16_t)];
    } un = {.a = 0x0102};
    if (un.b[0] == 1 && un.b[1] == 2)
        printf("big-endian\n");
    else if (un.b[1] == 1 && un.b[0] == 2)
        printf("small-endian\n");
    return 0;
}
