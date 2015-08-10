/*
 * Some code snippets for sharing.
 * Recipes:      https://github.com/tangwz/recipes
 * Author:       Tangwz
 * Data:         2015/6/25
 * Blog:         tangwz.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int fd;
	int n, i;
	char buff[1024];
	time_t tp;

	printf("I am %d process.\n", getpid());

	if((fd = open("fifo1", O_RWONLY)) < 0){
		perror("Open FIFO failed!");
		exit(1);
	}

	for(i = 0; i < 10; ++i){
		/* system time */
		time(&tp);
		n = sprintf(buff, "Process %d's time is %s", getpid(), ctime(&tp));
		printf("Send message: %s\n", buff);
		if(write(fd, buff, n + 1) < 0){
			perror("Write FIFO failed!");
			close(fd);
			exit(1);
		}
		sleep(1);
	}

	close(1);
	return 0;
}