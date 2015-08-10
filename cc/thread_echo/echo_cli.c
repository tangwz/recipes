#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

#define MAXLINE   2048
#define SERV_PORT 8888

size_t my_write(int sock_fd, const void *vptr, size_t n) {
  size_t left = n;
  size_t nwritten = 0;
  const char *p = vptr;
  while (left > 0) {
    if ((nwritten = write(sock_fd, p, left)) <= 0) {
      if (nwritten < 0 && errno == EINTR)
        nwritten = 0;
      else
        return -1;
    }
    left -= nwritten;
    p += nwritten;
  }
  return n;
}

static int read_cnt;
static char *read_ptr;
static char read_buf[MAXLINE];

int my_read(int sock_fd, char *c) {
  if (read_cnt <= 0) {
again:
    if ((read_cnt = read(sock_fd, read_buf, sizeof(read_buf))) < 0) {
      if (read_cnt < 0 && errno == EINTR)
        goto again;
      return -1;
    } else if (read_cnt == 0) {
      return 0;
    }
    read_ptr = read_buf;
  }
  read_cnt--;
  *c = *read_ptr++;
  return 1;
}

size_t read_line(int sock_fd, char *buf, size_t max) {
  size_t n, rc;
  char c;
  char *p = buf;
  for (n = 1; n < max; n++) {
    if ((rc = my_read(sock_fd, &c)) == 1) {
      *p++ = c;
      if (c == '\n')
        break;
    } else if (rc == 0) {
      *p = '\0';
      return n - 1;
    } else {
      return -1;
    }
  }
  *p = '\0';
  return n;
}


void *copyto(void *);

//global for both threads to access
static int  sockfd;
static FILE *fp;

void str_cli(FILE *fp_arg, int sockfd_arg)
{
  char      recvline[MAXLINE];
  pthread_t tid;

  sockfd = sockfd_arg;
  fp     = fp_arg;

  pthread_create(&tid, NULL, copyto, NULL);
  while(read_line(sockfd, recvline, MAXLINE) > 0)
      fputs(recvline, stdout);
}

void *copyto(void *arg)
{
  char sendline[MAXLINE];

  while(fgets(sendline, MAXLINE, fp) != NULL)
    my_write(sockfd, sendline, strlen(sendline));

  //EOF on stdin, send FIN
  shutdown(sockfd, SHUT_WR);
}


int main(int argc, char *argv[]) {
  int client_fd;
  struct sockaddr_in server_addr;
  if (argc != 2) {
    printf("error: use <filename>IpAddress.\n");
    return -1;
  }
  client_fd = socket(AF_INET, SOCK_STREAM, 0);
  
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERV_PORT);
  inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
  
  connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  
  str_cli(stdin, client_fd);
  return 0;
} 
