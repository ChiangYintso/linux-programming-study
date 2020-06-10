//
// Created by jiang on 2020/6/5.
//

#include <stdio.h>
#include <string.h>

static unsigned int clk = 0;
static unsigned int time_slice;
static int next_pid = 0;
unsigned int PCB[100];

struct Queue {
#define SIZE 100
    unsigned int queue[SIZE];
    int s;
    int e;
};

static inline void q_push(struct Queue *q, unsigned int pid) {
    q->queue[q->e] = pid;
    q->e = (q->e + 1) % SIZE;
}

static inline unsigned int q_pop(struct Queue *q) {
    int i = q->s;
    q->s = (q->s + 1) % SIZE;
    return q->queue[i];
}

static inline _Bool is_empty(struct Queue *q) {
    return q->s == q->e;
}

static inline void process_create(unsigned int interval) {
    PCB[++next_pid] = interval;
}

static inline void process_run(unsigned int pid) {
    printf("pid %u 在运行; ", pid);
}

static void schedule(int n,
                     const unsigned int *restrict sched_arrive,
                     const unsigned int *restrict sched_interval) {
    struct Queue q;
    bzero(&q, sizeof(struct Queue));

    unsigned int cur_run_interval = 0;
    unsigned int cur_pid = 0;

    while (next_pid < n || !is_empty(&q) || PCB[cur_pid]) {
        if (next_pid < n && sched_arrive[next_pid] == clk) {
            process_create(sched_interval[next_pid]);
            q_push(&q, next_pid);
        }

        if (!cur_pid && !is_empty(&q))
            cur_pid = q_pop(&q);

        printf("clk %2d: ", clk++);
        if (cur_pid) {
            if (PCB[cur_pid] == 0 || cur_run_interval == time_slice) {
                cur_run_interval = 0;
                if (PCB[cur_pid])
                    q_push(&q, cur_pid);
                cur_pid = is_empty(&q) ? 0 : q_pop(&q);
            }
            process_run(cur_pid);
            --PCB[cur_pid];
            ++cur_run_interval;
        }

        printf("\n等待队列：");
        for (int i = q.s; i != q.e; i = (i + 1) % SIZE)
            printf("%u ", q.queue[i]);
        printf("\n剩余时间：");
        for (int i = q.s; i != q.e; i = (i + 1) % SIZE)
            printf("%u ", PCB[q.queue[i]]);
        puts("\n---------------------------");
    }
}


int main() {
    puts("输入时间片长度");
    scanf("%u", &time_slice);
    int n;
    puts("输入需要创建的进程数");
    scanf("%d", &n);
    printf("输入%d行，每行两个数，创建时间和需要的时间间隔\n", n);

    unsigned int sched_arrive[n];
    unsigned int sched_interval[n];
    for (int i = 0; i < n; ++i)
        scanf("%u %u", sched_arrive + i, sched_interval + i);

    schedule(n, sched_arrive, sched_interval);
    return 0;
}
