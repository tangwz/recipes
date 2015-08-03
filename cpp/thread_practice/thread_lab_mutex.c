#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

int num = 0;

//add mutex
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;

void *add(void *arg)//add 500 times
{
  int i = 0,tmp;
  for(; i < 500; i++){
    pthread_mutex_lock(&mylock);
    tmp = num + 1;
    num = tmp;
    printf("+1, result is:%d\n",num);
    pthread_mutex_unlock(&mylock);
  }
}

void *sub(void *arg)//sub 500 times
{
  int tmp;
  for(int i = 0; i < 500; i++){
    pthread_mutex_lock(&mylock);
    tmp = num - 1;
    num = tmp;
    printf("-1,result is:%d\n",num);
    pthread_mutex_unlock(&mylock);
  }
}

int main(int argc, char *argv[]){
  pthread_t tid1,tid2;
  int err;
  void *tret;
  err = pthread_create(&tid1,NULL,add,NULL);
  if(err != 0){
    printf("pthread_create error : %s\n",strerror(err));
    exit(-1);
  }

  err = pthread_create(&tid2,NULL,sub,NULL);
  if(err != 0 ){
    printf("pthread_create error : %s\n",strerror(err));
    exit(-1);
  }

  err = pthread_join(tid1, &tret);//wait tid1 quit

  if(err != 0){
    printf("pthread_join error");
    exit(-1);
  }

  printf("pthread1 exit code : %d\n",tret);

  err = pthread_join(tid2, &tret);

  if(err != 0){
    printf("pthread_join error");
    exit(-1);
  }

  printf("pthread2 exit code: %d\n",tret);

  return 0;
}
