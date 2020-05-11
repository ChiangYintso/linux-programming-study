//
// Created by jiang on 2020/5/11.
//

#ifndef THREAD_BLOCK_QUEUE_H
#define THREAD_BLOCK_QUEUE_H

#include <stdbool.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MEM_SIZE 8 // actual queue size is 7

typedef struct {
    int queue[QUEUE_MEM_SIZE];
    int head;
    int tail;
    sem_t produce_sem;
    sem_t consume_sem;
    sem_t mutex;
} BlockQueue;

void bq_init(BlockQueue *bq);

int bq_pop(BlockQueue *bq);

void bq_push(BlockQueue *bq, int val);

static inline bool bq_is_full(BlockQueue *bq) {
    return (bq->tail + 1) % QUEUE_MEM_SIZE == bq->head;
}

static inline bool bq_is_empty(BlockQueue *bq) {
    return bq->tail == bq->head;
}

static inline int bq_count(BlockQueue *bq) {
    return (bq->tail - bq->head + QUEUE_MEM_SIZE) % QUEUE_MEM_SIZE;
}

#endif //THREAD_BLOCK_QUEUE_H
