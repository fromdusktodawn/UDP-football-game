/*************************************************************************
	> File Name: thread_pool.h
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年06月09日 星期二 18时14分20秒
 ************************************************************************/

#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#include "head.h"
#define MAXTASK 100
#define MAXTHREAD 10

typedef struct task_queue {
    int sum, epollfd, head, tail;
    struct User **team;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} task_queue;

void task_queue_init(struct task_queue *taskQueue, int sum, int epollfd);
void task_queue_push(struct task_queue *taskQueue, struct User *User);
struct User *task_queue_pop(struct task_queue *taskQueue);
void *thread_run(void *arg);

#endif
