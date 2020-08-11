//
// Created by jiang on 2020/5/20.
//
#include <stdio.h>

char a[4];

void func();

int main() {
    printf("%lu %lu %s\n", &a, sizeof(a), a);
    func();
    printf("%lu %lu %s\n", &a, sizeof(a), a);
    return 0;
}