#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<netinet/in.h>

#define MAXLINE 4096
#define SERV_PORT 9877

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

void str_client(FILE *fp, int sock_fd) {
  char sendline[MAXLINE];
  char recvline[MAXLINE];
  size_t n;
  while (fgets(sendline, MAXLINE, fp) != NULL) {
    n = strlen(sendline);
    my_write(sock_fd, sendline, n);
    if (read_line(sock_fd, recvline, MAXLINE) == 0) {
      printf("error:client read from server failed.\n");

    }
    fputs(recvline, stdout);

  }

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
  str_client(stdin, client_fd);
  return 0;

} 

