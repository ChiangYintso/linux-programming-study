//
// Created by jiang on 2020/5/11.
//

#include <pthread.h>
#include <unistd.h>
#include "block_queue.h"

static pthread_barrier_t barrier;

static void *consume(void *args) {
    pthread_barrier_wait(&barrier);
    BlockQueue *bq = args;
    for (int i = 0; i < 1000; ++i) {
        sleep(1);
        bq_pop(bq);
    }
}

static void *produce(void *args) {
    pthread_barrier_wait(&barrier);
    BlockQueue *bq = args;
    for (int i = 0; i < 1000; ++i) {
        sleep(9);
        bq_push(bq, i);
    }
}

int main() {
    BlockQueue block_queue;
    bq_init(&block_queue, 7);


    pthread_barrier_init(&barrier, NULL, 2);

    pthread_t consumer_t, producer_t;
    pthread_create(&consumer_t, NULL, &consume, &block_queue);
    pthread_create(&producer_t, NULL, &produce, &block_queue);

    void* res;
    pthread_join(consumer_t, &res);
    pthread_join(producer_t, &res);
    bq_destroy(&block_queue);
    pthread_barrier_destroy(&barrier);

    return 0;
}