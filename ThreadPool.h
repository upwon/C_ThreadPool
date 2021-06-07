/**
* File Name: ThreadPool.h
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


#ifndef C_THREADPOOL_THREADPOOL_H
#define C_THREADPOOL_THREADPOOL_H

typedef struct ThreadPool ThreadPool;

// 创建线程池
ThreadPool* CreateThreadPool(int minNumThreads, int maxNumThreads_, int queueSize_);


// 销毁线程池

// 添加任务至线程池

// 获取线程池中的工作线程

// 获取线程池中活着的线程池


_Noreturn void* worker(void* arg);

void* manager(void* arg);

void* threadExit(ThreadPool* pool);

#endif //C_THREADPOOL_THREADPOOL_H
