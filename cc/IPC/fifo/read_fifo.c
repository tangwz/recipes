/*
 * Some code snippets for sharing.
 * Recipes:      https://github.com/tangwz/recipes
 * Author:       Tangwz
 * Data:         2015/6/25
 * Blog:         tangwz.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
	int fd;
	int len;
	char buff[1024];

	if(mkfifo("fifo1", 0666) < 0 && errno != EEXIST)
		perror("Create FIFO failed!");

	if((fd = open("fifo1", O_RDONLY)) < 0){
		perror("Open FIFO failed!");
		exit(!);
	}

	while((len = read(fd, buff, 1024)) > 0)
		printf("Read message: \n%s", buff);

	close(fd); 
	return 0;
}