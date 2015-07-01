#include "pthread.h"

pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv)
{
	int   i;
	void  sig_int(int), thread_make(int);

	if(argc == 2)
		listenfd = tcp_listen(NULL, argv[1], &addrlen);
	if(argc == 3)
		listenfd = tcp_listen(argv[1], argv[2], &addrlen);
	else
		perror("usage: serv [ <host> ] <port#>");
	nthreads = atoi(argv[argc - 1]);
	tptr = calloc(nthreads, sizeof(Thread));

	for(i = 0; i < nthreads; ++i)
		thread_make(i);

	signal(SIGINT, sig_int);

	while(1){
		pause();
	}
}

void sig_int(int signo)
{
	int  i;
	void pr_cpu_time(void);

	/* terminate all children */
	for(i = 0; i < nchildren; ++i)
		kill(pids[i], SIGTERM);

	while(wait(NULL) > 0) /* wait for all children */
		;
	if(errno != ECHILD)
		perror("waite error");

	pr_cpu_time();
	exit(0);
}