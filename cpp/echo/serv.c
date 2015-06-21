#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<netinet/in.h>
#include<sys/wait.h>
#include<signal.h>

#define MAXLINE 4096
#define LISTEN_NUM 1024
#define SERV_PORT 9877

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
  pid_t pid;
  int listen_fd, client_fd;
  struct sockaddr_in server_addr, client_addr;
  if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("error: create listen socket failed.\n");
    return -1;

  }
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERV_PORT);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  listen(listen_fd, LISTEN_NUM);
  signal(SIGCHLD, sig_child);
  while (1) {
    len = sizeof(client_addr);
    client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &len);
    if ((pid = fork()) == 0) {
      close(listen_fd);
      str_echo(client_fd);
      exit(0);

    }
    close(client_fd);

  }
  return 0;

}

