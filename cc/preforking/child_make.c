#include "lib.h"

/*
 * 派生各个子进程
 */

pid_t child_make(int i, int listenfd, int addrlen)
{
	pid_t pid;
	void  child_main(int, int, int);

	if( (pid = fork()) > 0)
		return pid; /* parent */

	child_main(i, listenfd, addrlen); /* never returns */
}