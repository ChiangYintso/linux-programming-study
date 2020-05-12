//
// Created by jiang on 2020/5/12.
//

#include <stdio.h>

//#include "bar.h"
int max(int, int);

static int a = 9;

int max(int a, int b);
int main() {
    char *s = "hello world";
    char *s2 = "hello world";
    char *s3 = "hello";
//    s[2] = 'a';
    printf("%d\n", s == s2);
    printf("%d\n", s == s3);
//    a = 2;
    printf("%d", a);
    printf("%d", max(3, 4));
    return 0;
}