#include "lib.h"
#include <pthread.h>

typedef struct {
	pthread_t thread_tid;  /* thread ID */
	long      thread_count;/* # connections handled */
} Thread;
Thread *tptr;

int 			listenfd, nthreads;
socklen_t 		addrlen;
pthread_mutex_t mlock;