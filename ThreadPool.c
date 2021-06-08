/**
* File Name: ThreadPool.cpp
* Description: 用于详细说明此程序文件完成的主要功能，与其他模块或函数的接口，输出值、取值范围、含义及参数间的控制、顺序、独立或依赖等关系
*
* Author: Xianwen Wang
* Version: v1.0
* Date: 2021/6/7 15:46
* LastEditTime: 2021/6/7 15:46
* Copyright: Xianwen Wang
* Project Name: C_ThreadPool
* IDE: CLion
* Reference:
* History: 修改历史记录列表， 每条修改记录应包括修改日期、修改者及修改内容简述
*/
//

#include "ThreadPool.h"
#include<pthread.h>
#include<stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define  NUMBER  2
// 任务结构体
typedef struct Task
{
    void (*functions)(void *arg);

    void *arg;
} Task;

// 线程池结构体
struct ThreadPool
{
    // 任务队列
    Task *taskQueue;
    int queueCapacity; //容量
    int queueSize;     // 当前任务数量
    int queueFront;    //队头 -> 取数据
    int queueRear;     // 队尾 -> 放数据

    // 管理者线程与工作线程
    pthread_t threadManagerID;    // 管理者线程ID
    pthread_t *threadIDs;    //工作线程ID

    int minNumThreads; // 最小线程数量
    int maxNumThreads; // 最大线程数量
    int busyNumThreads; // 忙的线程数量
    int liveNumThreads; // 存活的线程个数
    int destroyNumThreads; // 要销毁的线程个数

    // 互斥锁
    pthread_mutex_t mutexPool; //锁整个线程
    pthread_mutex_t mutexBusy; //专用于锁busyNumThreads

    // 条件变量
    pthread_cond_t notFull; // 任务队列是不是满了
    pthread_cond_t notEmpty; // 任务队列是不是空了


    // 销毁线程标志
    bool shutdownThreadPool; //true表示销毁线程

};

ThreadPool *CreateThreadPool(int minNumThreads_, int maxNumThreads_, int queueSize_)
{

    ThreadPool *pool = (ThreadPool *) malloc(sizeof(ThreadPool));


    do
    {
        if (pool == NULL)
        {
            printf("malloc threadpool failure \n");
            break;
        }

        pool->threadIDs = (pthread_t *) malloc(sizeof(pthread_t) * maxNumThreads_);  // 类型 乘以 数量
        if (pool->threadIDs == NULL)
        {
            printf("malloc threadIDs failure \n");
            break;
        }
        memset(pool->threadIDs, 0, sizeof(pool->threadIDs) * maxNumThreads_); // 初始化


        pool->minNumThreads = minNumThreads_;
        pool->maxNumThreads = maxNumThreads_;
        pool->busyNumThreads = 0;
        pool->liveNumThreads = minNumThreads_; // 与最小个数相等
        pool->destroyNumThreads = 0;

        // 初始化互斥锁与条件量
        if (pthread_mutex_init(&pool->mutexPool, NULL) != 0 || pthread_mutex_init(&pool->mutexBusy, NULL) != 0 ||
            pthread_cond_init(&pool->notFull, NULL) != 0 || pthread_cond_init(&pool->notFull, NULL) != 0)
        {
            printf("mutex or pthread_cond  initialization failure \n");
            break;
        }

        // 初始化任务队列
        pool->taskQueue = (Task *) malloc(sizeof(Task) * queueSize_);
        pool->queueCapacity = queueSize_;
        pool->queueSize = 0;
        pool->queueFront = 0;
        pool->queueRear = 0;

        pool->shutdownThreadPool = false; // 默认不销毁


        // 创建线程
        pthread_create(&pool->threadManagerID, NULL, manager, pool);    // 创建管理者线程
        for (int i = 0; i < pool->minNumThreads; i++)   // 创建工作线程
        {
            pthread_create(&pool->threadIDs[i], NULL, worker, pool);
        }

    } while (0);

    // 释放资源
    if (pool && pool->threadIDs)
    {
        free(pool->threadIDs);
    }
    if (pool && pool->taskQueue)
    {
        free(pool->taskQueue);
    }


}


_Noreturn void *worker(void *arg)
{
    ThreadPool *pool = (ThreadPool *) arg;

    while (true)
    {
        pthread_mutex_lock(&pool->mutexPool);    // 加锁

        // 当前任务队列是否为空
        while (pool->queueSize == 0 && !pool->shutdownThreadPool)
        {
            // 阻塞工作线程ID
            pthread_cond_wait(&pool->notEmpty, &pool->mutexPool);

            // 线程阻塞函数, 哪个线程调用这个函数, 哪个线程就会被阻塞
//            int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
//            通过函数原型可以看出，该函数在阻塞线程的时候，需要一个互斥锁参数，这个互斥锁主要功能是进行线程同步，让线程顺序进入临界区，避免出现数共享资源的数据混乱。该函数会对这个互斥锁做以下几件事情：
//
//            在阻塞线程时候，如果线程已经对互斥锁 mutex 上锁，那么会将这把锁打开，这样做是为了避免死锁
//            当线程解除阻塞的时候，函数内部会帮助这个线程再次将这个 mutex 互斥锁锁上，继续向下访问临界区


            // 判断是不是要销毁线程
            if (pool->destroyNumThreads > 0)
            {

                pool->destroyNumThreads--;

                if (pool->liveNumThreads > pool->minNumThreads)
                {
                    pool->liveNumThreads--;
                    pthread_mutex_unlock(&pool->mutexPool);

                    //   pthread_exit(NULL);
                    threadExit(pool);  // 销毁当前线程
                }


            }

        }

        // 判断线程池是否被关闭了
        if (pool->shutdownThreadPool)
        {
            pthread_mutex_unlock(&pool->mutexPool);

            //pthread_exit(NULL);
            threadExit(pool);
        }

        // 从任务队列中取出一个任务
        Task task;
        task.functions = pool->taskQueue[pool->queueFront].functions;
        task.arg = pool->taskQueue[pool->queueFront].arg;

        // 移动头节点
        pool->queueFront = (pool->queueFront + 1) % pool->queueCapacity;
        pool->queueSize--;

        pthread_cond_signal(&pool->notFull);   // 唤醒生产者

        pthread_mutex_unlock(&pool->mutexPool);  // 解锁


        printf("thread %ld start working --- \n", pthread_self());
        pthread_mutex_lock(&pool->mutexBusy);   // busyNumThreads 专用的互斥锁
        pool->busyNumThreads++;
        pthread_mutex_unlock(&pool->mutexBusy);

        task.functions(arg);    // 工作
        free(task.arg);
        task.arg = NULL;

        printf("thread %ld end working --- \n", pthread_self());

        pthread_mutex_lock(&pool->mutexBusy);   // busyNumThreads 专用的互斥锁
        pool->busyNumThreads--;     // 工作结束后--
        pthread_mutex_unlock(&pool->mutexBusy);
    }

    //  return NULL;
}

void *manager(void *arg)
{
    ThreadPool *pool = (ThreadPool *) arg;

    while (!pool->shutdownThreadPool)
    {

        //每隔3秒检测一次
        sleep(3);

        // 取出线程池中任务的数量和当前线程的数量
        pthread_mutex_lock(&pool->mutexPool);
        int queueSize = pool->queueSize;
        int liveNum = pool->liveNumThreads;
        pthread_mutex_unlock(&pool->mutexPool);

        // 取出忙的线程的数量
        pthread_mutex_lock(&pool->mutexBusy);
        int busyNum = pool->busyNumThreads;
        pthread_mutex_unlock(&pool->mutexBusy);

        // 添加线程算法
        // 任务的个数>存活的线程个数 && 存活的线程数< 最大线程数
        if (queueSize > liveNum && liveNum < pool->maxNumThreads)
        {
            pthread_mutex_lock(&pool->mutexPool);
            int counter = 0;
            for (int i = 0; i < pool->maxNumThreads && counter < NUMBER && liveNum < pool->maxNumThreads; i++)
            {
                if (pool->threadIDs[i] == 0)  // 找到空位 即 数组中空闲的位置
                {
                    pthread_create(&pool->threadIDs[i], NULL, worker, pool);
                    counter++;
                    pool->liveNumThreads++;
                }
            }
            pthread_mutex_unlock(&pool->mutexPool);


        }

        // 销毁线程算法
        // 忙的线程*2 < 存活的线程个数 && 存活的线程 > 最小线程数
        if (busyNum * 2 < liveNum && liveNum > pool->minNumThreads)
        {
            pthread_mutex_lock(&pool->mutexPool);

            pool->destroyNumThreads = NUMBER;
            pthread_mutex_unlock(&pool->mutexPool);

            // 让工作的线程自杀
            for (int i = 0; i < NUMBER; i++)
            {
                pthread_cond_signal(&pool->notEmpty);
            }


        }


    }
}

/// 线程退出时 更改数组中的值为0  作为记录
/// \param pool
/// \return
void *threadExit(ThreadPool *pool)
{
    pthread_t tid = pthread_self();

    for (int i = 0; i < pool->maxNumThreads; i++)
    {
        if (pool->threadIDs[i] == tid)
        {
            pool->threadIDs[i] = 0;
            printf("threadExit() called , %ld exiting --- \n", tid);
        }
    }

    pthread_exit(NULL);  // 当前线程退出


}


// 给线程池添加任务
void threadPoolAdd(ThreadPool *pool, void(*func)(void *), void *arg)
{
    pthread_mutex_lock(&pool->mutexPool);

    // 生产者 阻塞 当容量满了 并且 没有销毁线程池
    while (pool->queueSize == pool->queueCapacity && !pool->shutdownThreadPool)
    {

        // 阻塞生产者线程
        pthread_cond_wait(&pool->notFull, &pool->mutexPool);

    }

    if (pool->shutdownThreadPool)
    {
        pthread_mutex_unlock(&pool->mutexPool);
        return;
    }

    // 添加任务
    pool->taskQueue[pool->queueRear].functions = func;
    pool->taskQueue[pool->queueRear].arg = arg;
    pool->queueRear = (pool->queueRear + 1) % pool->queueCapacity;  // 环形队列
    pool->queueSize++;


    pthread_cond_signal(&pool->notEmpty);   // 唤醒消费者
    pthread_mutex_unlock(&pool->mutexPool);

}


int threadPoolLiveNum(ThreadPool *pool)
{
    pthread_mutex_lock(&pool->mutexBusy);

    int busyNum = pool->busyNumThreads;

    pthread_mutex_unlock(&pool->mutexBusy);
    return busyNum;
}


int threadPoolWorkNum(ThreadPool *pool)
{

    pthread_mutex_lock(&pool->mutexPool);
    int workNum = pool->liveNumThreads;   // 关闭线程

    pthread_mutex_unlock(&pool->mutexPool);
    return workNum;

}


int threadPoolDestroy(ThreadPool *pool)
{
    if (pool == NULL)
    {
        return -1;   // 对于空的 pool
    }
    // 阻塞回收管理线程
    pthread_join(pool->threadManagerID, NULL);

    // 唤醒阻塞的消费者线程ID
    for (int i = 0; i < pool->liveNumThreads; i++)
    {
        pthread_cond_signal(&pool->notEmpty);
    }

    // 释放堆区
    if (pool->taskQueue)
    {
        free(pool->taskQueue);
        pool->taskQueue = NULL;
    }
    if (pool->threadIDs)
    {
        free(pool->threadIDs);
        pool->threadIDs = NULL;
    }

    // 释放互斥锁以及条件变量
    pthread_mutex_destroy(&pool->mutexPool);
    pthread_mutex_destroy(&pool->mutexBusy);

    pthread_cond_destroy(&pool->notEmpty);
    pthread_cond_destroy(&pool->notFull);


    free(pool);
    pool = NULL;

    return 1;
}