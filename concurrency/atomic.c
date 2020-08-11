//
// Created by jiang on 2020/4/20.
//

#include <pthread.h>
#include <stdio.h>
#include <stdatomic.h>

_Atomic long counter;
long counter2 = 0;

void *thread_func(void *args) {
    for (int i = 0; i < 10000; ++i) {
        atomic_fetch_add(&counter, 1);
        counter2++;
    }
    return args;
}

int main() {
    atomic_init(&counter, 12);
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread_func, NULL);
    pthread_create(&thread2, NULL, thread_func, NULL);
    void *res;
    pthread_join(thread1, &res);
    pthread_join(thread2, &res);
    printf("%lld\n", counter);
    printf("%lld\n", counter2);
    return 0;
}