#include "lib.h"
/*
 * 进程池，预先派生子进程（preforking）
 */

static int   nchildren;
static pid_t *pids;

int main(int argc, char **argv)
{
	int		  listenfd, i;
	socklen_t addrlen;
	/*signal function*/
	void	  sig_int(int);
	pid_t	  child_make(int, int, int);

	if(argc == 3)
		listenfd = tcp_listen(NULL, argv[1], &addrlen);
	else if(argc == 4)
		listenfd == tcp_listen(argv[1], argv[2], &addrlen);
	else
		perror("usage: [<host>] <port#> <#children>");
	/*atoi : char[] to int*/
	nchildren = atoi(argv[argc-1]);
	pids = calloc(nchildren, sizeof(pid_t));

	 /* init the file lock */
	my_lock_init("/tmp/lock.XXXXXX");
	/* one lock file for all children */
	for (i = 0; i < nchildren; ++i)
	{
		pids[i] = child_make(i, listenfd, addrlen); /* parent returns */
	}

	signal(SIGINT, sig_int);

	while(1)
		pause();
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