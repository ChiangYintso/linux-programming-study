//
// Created by jiang on 2020/5/11.
//

#include <stdio.h>
#include <stdlib.h>

_Noreturn void hello() {
    printf("hello ");

    _Generic(2, int:printf("hello"), float:printf("world"));
    exit(0);
}

int main() {
    hello();
}