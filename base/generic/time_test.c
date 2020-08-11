//
// Created by jiang on 2020/7/25.
//

#include <stdio.h>
#include <time.h>

int main() {
    int a = 0;
    clock_t t = clock();

    for (int i = 0; i < 1000000000; i++) {
    }
    t = (clock() - t);
    printf("%ld", t);
    return 0;
}