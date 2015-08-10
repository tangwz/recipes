#include "lib.h"
/*
 * 每个子进程执行的无限循环
 */


void child_main(int i, int listenfd, int addrlen)
{
	int    	  connfd;
	void 	  web_child(int);
	socklen_t clilen;
	struct sockaddr *cliaddr;

	cliaddr = malloc(addrlen);
	printf("child %ld starting\n", (long) getpid());

	while(1){
		clilen = addrlen;

		my_lock_wait();
		connfd = accept(listenfd, cliaddr, &clilen);
		my_lock_release();

		web_child(connfd); /*process the request */
		close(connfd);
	}
}