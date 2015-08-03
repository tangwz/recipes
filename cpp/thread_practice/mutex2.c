#include <stdlib.h>
#include <pthread.h>

#define NHASH 29
#define HASH(id) (((unsigned long)id) % NHASH) 

struct foo *fh[NHASH]

pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo{
  int             f_count;
  pthread_mutex_t f_lock;
  int             f_id;
  struct foo      *f_next;
};

struct foo *
foo_alloc(int id)
{
  struct foo *fp;
  int        idx;

if
}
