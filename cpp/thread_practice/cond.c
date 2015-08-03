#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int num = 0;
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  qready = PTHREAD_COND_INITIALIZER;

void *thread_func(void *arg)
{
  int i = (long )arg;
  int ret;
  sleep(5-i);
  pthread_mutex_lock(&mylock);
  while(i != num){
#ifndef DEBUG
    printf("thread %d is waiting\n",i);
#endif
    ret = pthread_cond_wait(&qready, &mylock);
    if(ret == 0){
#ifndef DEBUG
      printf("thread %d waite success!\n",i);
#endif
    }else{
#ifndef DEBUG
      printf("tthread %d waite error: %s\n",i,strerror(ret));
#endif
    }
  }
  printf("thread %d is running!\n",i);
  num++;
  pthread_mutex_unlock(&mylock);
  pthread_cond_broadcast(&qready);
}

int main(int argc, char *argv[]){
  int i = 0, err;
  pthread_t tid[4];
  void *tret;
  for(; i < 4; i++){
    err = pthread_create(&tid[i],NULL,thread_func,(void *)i);
    if(err != 0){
      printf("thread %d create error : %s\n",i,strerror(err));
      exit(-1);
    }
  }

  for(int i = 0; i < 4; i++){
    err = pthread_join(tid[i],&tret);
    if(err != 0){
      printf("thread %d join error : %s\n",i,strerror(err));
      exit(-1);
    }
  }

  return 0;
}
