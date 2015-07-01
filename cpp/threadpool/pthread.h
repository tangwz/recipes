#include "lib.h"
#include <pthread.h>

typedef struct {
	pthread_t thread_tid;  /* thread ID */
	long      thread_count;/* # connection handled */
} Thread;
Thread *tptr;

#define MAXNCLI 32
int clifd[MAXNCLI], iget, iput;
pthread_mutex_t clifd_mutex;
pthread_cond_t  clifd_cond;