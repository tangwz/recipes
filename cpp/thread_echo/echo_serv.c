#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>
#include<errno.h>
#include<netinet/in.h>
#include<sys/wait.h>
#include<signal.h>
#include<pthread.h>

#define MAXLINE 4096
#define LISTEN_NUM 1024
#define SERV_PORT 9877

static void *doit(void *);

int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{
  int listenfd, n;
  const int on = 1;
  struct addrinfo hints, *res, *ressave;
  bzero(&hints, sizeof(hints));
  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  if ((n = getaddrinfo(host, serv, &hints, &res)) != 0) {
    printf("tcp_listen() error for %s, %s: %s\n", host, serv, gai_strerror(n));
    exit(1);

  }
  ressave = res;
  do {
    listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (listenfd < 0)
      continue;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
      printf("tcp_listen() error: %s\n", strerror(errno));
      exit(1);

    }
    if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
      break;
    close(listenfd);

  } while ((res = res->ai_next) != NULL);
  if (res == NULL) {
    printf("tcp_listen() error for %s, %s", host, serv);
    exit(1);

  }
  if (listen(listenfd, LISTEN_NUM) < 0) {
    printf("tcp_listen() error: %s\n", strerror(errno));
    exit(1);

  }
  if (addrlenp)
    *addrlenp = res->ai_addrlen;
  freeaddrinfo(ressave);
  return (listenfd);

}

size_t my_write(int sock_fd, const void *vptr, int n) {
  size_t left = n;
  size_t nwritten = 0;
  const char *p = vptr;
  while (left > 0) {
    if ((nwritten = write(sock_fd, p, left)) <= 0) {
      if (n < 0 && errno == EINTR)
        nwritten = 0;
      else
        return -1;

    }
    left -= nwritten;
    p += nwritten;

  }
  return n;

}

void str_echo(int sock_fd) {
  size_t nread;
  char buf[MAXLINE];

again:
  while ((nread = read(sock_fd, buf, MAXLINE)) > 0) {
    my_write(sock_fd, buf, nread);
  }
  if (nread < 0 && errno == EINTR)
    goto again;
  else if (nread < 0) {
    printf("error:server read from client failed.\n");
  }

}

void sig_child(int signo)
{
  pid_t pid;
  int stat;

  pid = wait(&stat);
  printf("child %d terminated\n", pid);
  return;
}

int main(int argc, char *argv[]) {
  socklen_t len;
  pid_t     pid;
  pthread_t  tid;
  int listen_fd, *iptr;
  struct sockaddr_in *client_addr;

  if(argc == 2)
    listen_fd = tcp_listen(NULL, argv[1], &len);
  else if(argc == 3)
    listen_fd = tcp_listen(argv[1], argv[2], &len);
  else
    perror("usage : [ <host> ] <service or port>");

  client_addr = malloc(len);

  signal(SIGCHLD, sig_child);

  while (1) {
    iptr = malloc(sizeof(int));
    *iptr = accept(listen_fd, client_addr, &len);
    pthread_create(&tid, NULL, &doit, iptr);
  }
  return 0;

}

static void* doit(void *arg)
{
  int connfd;

  connfd = *((int *) arg);
  free(arg);

  pthread_detach(pthread_self());
  str_echo(connfd);
  close(connfd);
}

