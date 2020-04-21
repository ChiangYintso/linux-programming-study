//
// Created by jiang on 2020/4/20.
//

#include <stdlib.h>
#include <stdio.h>

void foo() {
    printf("foo\n");
}

void bar() {
    printf("bar\n");
}

int main() {
    atexit(foo);
    atexit(bar);
    printf("hello world\n");
    return 0;
}