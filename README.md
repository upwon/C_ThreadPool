# C_ThreadPool
 Simple Thread Pool



The composition of the thread pool is mainly divided into three parts, these three parts work together to get a complete thread pool:



Task queue, which stores the tasks that need to be processed, and the threads of work handle these tasks

- Add a pending task to or delete from the task queue through the API function provided by the thread pool

- Processed tasks will be deleted from the task queue

- The user of the thread pool, that is, the thread that calls the thread pool function to add tasks to the task queue is the producer thread



Work threads (consumers of task queue tasks), N

- A certain number of worker threads are maintained in the thread pool. Their function is to constantly read the task queue, take out tasks from it and process them

- The thread of work is equivalent to the consumer role of the task queue,

- If the task queue is empty, the working thread will be blocked (using condition variable/semaphore blocking)

- If there is a new task after blocking, the producer will remove the blocking and the worker thread will start working



Manager thread (do not process tasks in the task queue), 1

- Its task is to periodically detect the number of tasks in the task queue and the number of busy worker threads

- When there are too many tasks, you can appropriately create some new worker threads



- When there are too few tasks, some working threads can be destroyed appropriately



 
