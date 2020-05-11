//
// Created by jiang on 2020/5/11.
//

#include <pthread.h>
#include <unistd.h>
#include "block_queue.h"

static void *consume(void *args) {
    BlockQueue *bq = args;
    for (int i = 0; i < 1000; ++i) {
        usleep(30);
        bq_pop(bq);
    }
}

static void *produce(void *args) {
    BlockQueue *bq = args;
    for (int i = 0; i < 1000; ++i) {
        usleep(i % 6);
        bq_push(bq, i);
    }
}

int main() {
    BlockQueue block_queue;
    bq_init(&block_queue);

    pthread_t consumer_t, producer_t;
    pthread_create(&consumer_t, NULL, &consume, &block_queue);
    pthread_create(&producer_t, NULL, &produce, &block_queue);

    void* res;
    pthread_join(consumer_t, &res);
    pthread_join(producer_t, &res);
    return 0;
}