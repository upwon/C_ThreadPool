#include <stdio.h>
#include <pthread.h>
#include"ThreadPool.h"
#include <stdlib.h>
#include <unistd.h>

void taskFunc(void *arg)
{
    int num=*(int*)arg; //转换后取值

    printf("thread %ld is working, number= %d \n",pthread_self(),num);

    sleep(1);
}

int main()
{

    // 创建线程池
    ThreadPool *pool = CreateThreadPool(3, 10, 100);

    for (int i = 0; i < 100; i++)
    {
        int* num=(int*)malloc(sizeof(int));
        *num=i+100;

        threadPoolAdd(pool,taskFunc,num);
    }

   // free(num);

    sleep(30);  // 睡眠30秒
    threadPoolDestroy(pool);


    printf("Hello, World!\n");
    return 0;
}
