//
// Created by jiang on 2020/5/11.
//

#ifndef THREAD_BLOCK_QUEUE_H
#define THREAD_BLOCK_QUEUE_H

#include <stdbool.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int Q_SIZE; // 队列的元素个数（比实际能存放的元素个数多1）
    int *queue; // 队列指针
    int head; // 队列头下标
    int tail; // 队列尾下标
    sem_t produce_sem; // 生产信号量，等于队列剩余容量
    sem_t consume_sem; // 消费信号量，等于队列当前长度
    sem_t mutex; // 互斥信号量，使pop和push同步
} BlockQueue;

/**
 * 初始化阻塞队列
 * @param bq 阻塞队列指针
 */
void bq_init(BlockQueue *bq, int size);

/**
 * 销毁阻塞队列：销毁信号量及释放队列内存
 * @param bq 阻塞队列指针
 */
void bq_destroy(BlockQueue *bq);

/**
 * 从队头取出一个元素。队空时，操作将阻塞，直到队列非空
 * @param bq 阻塞队列指针
 * @return 取出的元素
 */
int bq_pop(BlockQueue *bq);

/**
 * 向队尾添加一个元素，队满时，操作将阻塞，直到队列非满
 * @param bq 阻塞队列指针
 * @param val 待添加的元素
 */
void bq_push(BlockQueue *bq, int val);

/**
 * 判断队列是否满了
 * @param bq 阻塞队列指针
 * @return 满了: true; 没满: false
 */
static inline bool bq_is_full(BlockQueue *bq) {
    return (bq->tail + 1) % bq->Q_SIZE == bq->head;
}

/**
 * 判断队列是否为空
 * @param bq 阻塞队列指针
 * @return 空了: true; 非空: false
 */
static inline bool bq_is_empty(BlockQueue *bq) {
    return bq->tail == bq->head;
}

/**
 * 获取队列中元素个数
 * @param bq 阻塞队列指针
 * @return 元素个数
 */
static inline int bq_length(BlockQueue *bq) {
    return (bq->tail - bq->head + bq->Q_SIZE) % bq->Q_SIZE;
}

#endif // THREAD_BLOCK_QUEUE_H
