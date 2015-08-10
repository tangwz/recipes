#include "lib.h"
#include <sys/mman.h>

/*
 * 在不同进程之间使用线程锁的要求：
 * （1）互斥锁变量必须存放在由所有进程共享的内存区中；
 * （2）必须告知线程函数库这是在不同进程之间共享的互斥锁；
 *
 * 这要求线程库支持PTHREAD_PROCESS_SHARED属性
 */

static pthread_mutex_t *mptr;  /* actual mutex will be in shared memory */

 void my_lock_init(char *pathname)
 {
 	int 				fd;
 	pthread_mutexattr_t mattr;

 	fd = open("/dev/zero", O_RDWR, 0);

 	mptr = mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE,
 				MAP_SHARED, fd, 0);;
 	close(fd);

 	pthread_mutexattr_init(&mattr);
 	pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);
 	pthread_mutex_init(mptr, &mattr);
 }

 void my_lock_wait()
 {
 	pthread_mutex_lock(mptr);
 }

 void my_lock_release()
 {
 	pthread_mutex_unlock(mptr);
 }