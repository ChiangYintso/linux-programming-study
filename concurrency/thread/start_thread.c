//
// Created by jiang on 2020/4/20.
//

#include <pthread.h>
#include <stdio.h>

static int a = 0;

void *do_something(void *message) {
    printf("hello %s\n", (char *)message);
    for (int i = 0; i < 100000; ++i) {
        a++;
    }
    return message;
}

int main() {
    pthread_t thread1, thread2;
    char *msg1 = "Linux";
    char *msg2 = "gcc";

    pthread_create(&thread1, NULL, do_something, (void *)msg1);
    pthread_create(&thread2, NULL, do_something, (void *)msg2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("a = %d\n", a);
    return 0;
}
