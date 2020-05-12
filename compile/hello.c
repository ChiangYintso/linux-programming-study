#include <stdbool.h>
#include <stdio.h>
#include "mymath.h"

#ifndef a
#define a b
#endif

int main() {
    // can't see me
    bool a = true;
    printf("hello %d", add(4, b));
    return 0;
}
