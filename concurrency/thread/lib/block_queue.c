//
// Created by jiang on 2020/5/11.
//

#include "block_queue.h"

void bq_init(BlockQueue *bq, int size) {
    bq->Q_SIZE = size + 1;
    if (sem_init(&bq->produce_sem, 0, bq->Q_SIZE - 1) != 0 ||
        sem_init(&bq->consume_sem, 0, 0) != 0 ||
        sem_init(&bq->mutex, 0, 1) != 0) {
        perror("bq_init");
        exit(EXIT_FAILURE);
    }
    bq->queue = malloc(sizeof(int) * size);
    bq->head = bq->tail = 0;
}

void bq_destroy(BlockQueue *bq) {
    free(bq->queue);
    sem_destroy(&bq->mutex);
    sem_destroy(&bq->consume_sem);
    sem_destroy(&bq->produce_sem);
}

int bq_pop(BlockQueue *bq) {
    sem_wait(&bq->consume_sem);
    sem_wait(&bq->mutex);
    int result = bq->queue[bq->head];
    bq->head = (bq->head + 1) % bq->Q_SIZE;
#ifdef DEBUG
    printf("consume %d, capacity of queue: %d\n", result, bq_length(bq));
#endif
    sem_post(&bq->mutex);
    sem_post(&bq->produce_sem);
    return result;
}

void bq_push(BlockQueue *bq, int val) {
    sem_wait(&bq->produce_sem);
    sem_wait(&bq->mutex);
    bq->queue[bq->tail] = val;
    bq->tail = (bq->tail + 1) % bq->Q_SIZE;
#ifdef DEBUG
    printf("produce %d, capacity of queue: %d\n", val, bq_length(bq));
#endif
    sem_post(&bq->mutex);
    sem_post(&bq->consume_sem);
}
