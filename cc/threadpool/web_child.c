#include "lib.h"

#define MAXLINE 1024
#define MAXN 	16384

void web_child(int sockfd)
{
	int     ntowrite;
	ssize_t nread;
	char    line[MAXLINE], result[MAXN];

	while(1){
		if( (nread = read_line(sockfd, line, MAXLINE)) == 0)
			return;   /* connection closed by other end */

			/* line from client specifies #bytes to write back */
		ntowrite = atol(line);
		if( (ntowrite <= 0) || (ntowrite > MAXN))
			fprintf(stderr, "client request for %d bytes", ntowrite);
		
		my_write(sockfd, result, ntowrite);
	}
}