#include "child.h"

static int nchildren;

int main(int argc, char **argv)
{
	int       listenfd, i, navail, maxfd, nsel, connfd, rc;
	void      sig_int(int);
	pid_t     child_make(int, int, int);
	ssize_t   n;
	fd_set    rset, masterset;
	socklen_t addrlen, clilen;
	struct sockaddr* cliaddr;

	if(argc == 3)
		listenfd = tcp_listen(NULL, argv[1], &addrlen);
	else if(argc == 4)
		listenfd = tcp_listen(argv[1], argv[2], &addrlen);
	else
		perror("usage: serv [<host>] <port#> <#children>");

	FD_ZERO(&masterset);
	FD_SET(listenfd, &masterset);
	maxfd = listenfd;
	cliaddr = malloc(addrlen);

	nchildren = atoi(argv[argc - 1]);
	navail = nchildren;
	cptr = calloc(nchildren, sizeof(Child));

	/* prefork all thr children */
	for(i = 0; i < nchildren; ++i){
		child_make(i, listenfd, addrlen);  /* parent returns */
		FD_SET(cptr[i].child_pipefd, &masterset);
		maxfd = max(maxfd, cptr[i].child_pipefd);
	} 

	signal(SIGINT, sig_int);

	while(1){
		rset = masterset;
		if(navail <= 0)
			FD_CLR(listenfd, &rset);  /* turn off if no available children */
		nsel = select(maxfd + 1; &rset, NULL, NULL, NULL);

		/* check for new connection */
		if(FD_ISSET(listenfd, &rset)){
			clilen = addrlen;
			connfd = accept(listenfd, cliaddr, &clilen);

			for(i = 0; i < nchildren; ++i){
				if(cptr[i].child_status == 0)
					break;  /* available */
			}

			if(i == nchildren)
				perror("no available children");
			cptr[i].child_status = 1; /* mark child as busy */
			cptr[i].child_count++;
			navail--;

			n = write_fd(cptr[i].child_pipefd, "", 1, connfd);
			close(connfd);

			if(--nsel == 0)
				continue;  /* all done with select() results */
		}

		/*find any newly-available children */
		for(i = 0; i < nchildren; ++i){
			if(FD_ISSET(cptr[i].child_pipefd, &rset)){
				if( (n = my_read(cptr[i].child_pipefd, &rc, 1)) == 0)
					fprintf(stderr, "child %d terminated unexpectedly", i);
				cptr[i].child_status = 0;
				navail++;
				if(--nsel == 0)
					break;  /* all done with select() results */
			}
		}
	}
}