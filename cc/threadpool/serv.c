#include "pthread.h"

static int nthreads;
pthread_mutex_t clifd_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  clifd_cond  = PTHREAD_COND_INITIALIZER;

int main(int argc, char **argv)
{
	int i, listenfd, connfd;
	socklen_t addrlen, clilen;
	struct sockaddr* cliaddr;

	if(argc == 3)
		listenfd = tcp_listen(NULL, argv[1], &addrlen);
	if(argc == 4)
		listenfd = tcp_listen(argv[1], argv[2], &addrlen);
	else
		perror("usage: serv [<host>] <port#> <#threads>");
	nthreads = atoi(argv[argc - 1]);
	cliaddr = malloc(addrlen);
	tptr = calloc(nthreads, sizeof(Thread));
	
	iget = iput = 0;

	for(i = 0; i < nthreads; ++i)
		thread_make(i);

	signal(SIGINT, sig_int);

	while(1){
		clilen = addrlen;
		connfd = accept(listenfd, cliaddr, &clilen);

		pthread_mutex_lock(&clifd_mutex);
		clifd[iput] = connfd;
		if(++iput == MAXNCLI)
			iput = 0;
		if(iput == iget)
			fprintf(stderr, "iput = iget = %d", iput);

		pthread_cond_signal(&clifd_cond);
		pthread_mutex_unlock(&clifd_mutex);
	}

}