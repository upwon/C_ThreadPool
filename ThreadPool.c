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
    Pthread_mutex_t mutexBusy; //专用于锁busyNumThreads

    // 条件变量
    pthread_cond_t notFull; // 任务队列是不是满了
    pthread_cond_t notEmpty; // 任务队列是不是空了

    
    // 销毁线程标志
    bool shutdownThreadPool; //true表示销毁线程

};