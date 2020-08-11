//
// Created by jiang on 2020/5/23.
//

#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>

typedef struct A {
    char a;
    short b;
} A;

typedef struct B {
    short a;
    char b;
} B;

typedef struct C {
    char a;
    char b;
    short c;
    int d;
} C;

typedef struct D {
    char a;
    short b;
    char c;
    int d;
} D;

typedef struct __attribute__((__packed__)) E {
    char a;
    short b;
    char c;
    int d;
} E;

int main() {
    printf("%lu %lu %lu %lu %lu\n",
            sizeof(A), sizeof(B), sizeof(C), sizeof(D), sizeof(E));
    return 0;
}