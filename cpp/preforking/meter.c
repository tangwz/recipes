#include "lib.h"
#include <sys/mman.h>

/*
 * Allocate an array of "nchildren" longs in shared memory that can 
 * be used as a counter by each child of how many clients it services.
 */

long *meter(int nchildren)
{
	int  fd;
	long *ptr;

#ifndef MAP_ANON
	ptr = mmap(0, nchildren * sizeof(long), PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_SHARED, -1 ,0);
#else
	fd = open("/dev/zero", O_RDWR, 0);

	ptr = mmap(0, nchildren * sizeof(long), PROT_READ | PROT_WRITE,
				MAP_SHARED, fd, 0);

	close(fd);
#endif

	return ptr;
}