#include <stdio.h>
#include <pthread.h>
#include"ThreadPool.h"
#include <stdlib.h>
#include <unistd.h>

void taskFunc(void *arg)
{
  //  int num=*(int*)arg; //转换后取值
    int num=*(int*)arg;


    printf("thread %ld is working, number= %d \n",pthread_self(),num);

    sleep(1);
}

int main()
{
    // 创建线程池
    ThreadPool *pool = CreateThreadPool(3, 10, 100);

    int* ip = new int; //  1 allocates memory (4 bytes)
    //  2 creates int
    //  3 assigns its address to ip
    *ip = 12345;
    std::cout <<  *ip << std:endl;

    delete ip;  // de-allocates memory (frees it)


    for (int i = 0; i < 100; i++)
    { // int* num=(int*)malloc(sizeof(int));

      //  *num=i+100;
     //   int* num=new int(i+100);
        int* num = new int;
             *num=   (i + 100);

        printf("----%d----\n",*num);

        threadPoolAdd(pool,taskFunc,num);
    }

   // free(num);

    sleep(30);  // 睡眠30秒
    threadPoolDestroy(pool);


   /* int* num=(int*)malloc(sizeof(int));

    *num=100;
    taskFunc(num);

    printf("-------exit---------------\n");
    printf("Hello, World!\n");*/
    return 0;
}
