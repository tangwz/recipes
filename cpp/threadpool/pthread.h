#include "lib.h"
#include <pthread.h>

typedef struct {
	pthread_t thread_tid;  /* thread ID */
	long      thread_count;/* # connection handled */
} Thread;
Thread *tptr;

#define MAXNCLI 32
/*
 * clifd数组：由主线程往中存入已接受的已连接套接字描述符
 * iput：主线程将往该数组中存入的下一个元素的下标
 * iget：线程池中某个线程将从该数组中取出的下一个元素的下标
 * 注：这个由所有线程共享的数据结构自然必须得到保护！！！ 
 */
int clifd[MAXNCLI], iget, iput;
pthread_mutex_t clifd_mutex;
pthread_cond_t  clifd_cond;