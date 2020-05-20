//
// Created by jiang on 2020/5/20.
//
#include <stdio.h>

long long a = 0x6162;

void func() {
    a = 0x6364;
    printf("%lu %lu %c\n", &a, sizeof(a), a);
}