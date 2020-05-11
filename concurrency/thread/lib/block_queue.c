//
// Created by jiang on 2020/5/11.
//

#include "block_queue.h"

void bq_init(BlockQueue *bq) {
    if (sem_init(&bq->produce_sem, 0, QUEUE_MEM_SIZE - 1) != 0 ||
        sem_init(&bq->consume_sem, 0, 0) != 0 ||
        sem_init(&bq->mutex, 0, 1)) {
        perror("bq_init");
        exit(EXIT_FAILURE);
    }
    bq->head = bq->tail = 0;
}

int bq_pop(BlockQueue *bq) {
    sem_wait(&bq->consume_sem);
    sem_wait(&bq->mutex);
    int result = bq->queue[bq->head];
    bq->head = (bq->head + 1) % QUEUE_MEM_SIZE;
#ifdef DEBUG
    printf("consume %d, capacity of queue: %d\n", result, bq_count(bq));
#endif
    sem_post(&bq->mutex);
    sem_post(&bq->produce_sem);
    return result;
}

void bq_push(BlockQueue *bq, int val) {
    sem_wait(&bq->produce_sem);
    sem_wait(&bq->mutex);
    bq->queue[bq->tail] = val;
    bq->tail = (bq->tail + 1) % QUEUE_MEM_SIZE;
#ifdef DEBUG
    printf("produce %d, capacity of queue: %d\n", val, bq_count(bq));
#endif
    sem_post(&bq->mutex);
    sem_post(&bq->consume_sem);
}
