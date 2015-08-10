#include "pthread.h"

void thread_make(int i)
{
	void  *thread_main(void *);
	
	pthread_create(&tptr[i].thread_tid, NULL, &thread_main, (void *)i);
	return;
}

void *thread_main(void *arg)
{
	int connfd;
	void web_child(int);
	socklen_t clilen;
	struct sockaddr* cliaddr;

	cliaddr = malloc(addrlen);

	printf("thread %d starting\n", (int)arg);
	while(1){
		clilen = addrlen;
		pthread_mutex_t(&mlock);
		connfd = accept(listenfd, cliaddr, &cliaddr);
		pthread_mutex_unlock(&mlock);
		tptr[(int)arg].thread_count++;
		web_child(connfd);
		close(fd);
	}
}