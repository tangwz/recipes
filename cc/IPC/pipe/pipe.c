/*
 * Some code snippets for sharing.
 * Recipes:      https://github.com/tangwz/recipes
 * Author:       Tangwz
 * Data:         2015/6/25
 * Blog:         tangwz.com
 */

#include <stdio.h>
#include <unistd.h>

/*
 * 特点：
 * 它是半双工的（即数据只能在一个方向上流动），具有固定的读端和写端。
 * 
 * 它只能用于具有亲缘关系的进程之间的通信（也是父子进程或者兄弟进程之间）。
 * 
 * 它可以看成是一种特殊的文件，对于它的读写也可以使用普通的read、write 等函数。
 * 但是它不是普通的文件，并不属于其他任何文件系统，并且只存在于内存中。
 */

/* demo实现兄弟进程通信（父子也就那样） */
int main()
{
	
	int fd[2];
	pid_t pid1, pid2;
	char buff[20];

	/* 创建管道 */
	if(pipe(fd) < 0)
		perror("Create Pipe failed!\n");

	/* 创建子进程1 */
	if((pid1 = fork()) < 0)
		perror("Fork failed!\n");
	if(pid1 == 0){
		close(fd[0]);
		write(fd[1], "Hello Brother\n", 14);
		printf("I am child1 process: %d.\n", getpid());
		exit(0);
	}

	/* 创建子进程2 */
	if((pid2 = fork()) < 0)
		perror("Fork failed!\n");
	if(pid2 == 0){
		close(fd[1]);
		read(fd[0], buf, 20);
		printf("I am child2 process: %d.\n", getpid());
		exit(0);
	}else if(pid2 > 0){ /* 父进程 */
		close(fd[0]);
		close(fd[1]);
		printf("I am father process: %d.\n", getpid());
		printf("The message is : \n%s", buff);
		exit(0);
	}

	return 0;
}