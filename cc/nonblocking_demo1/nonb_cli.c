#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

#define SERV_PORT 8888

int setnonblocking(int sockfd)
{
  fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK);
  return 0;
}

int main(int argc, char* argv[])
{
  struct sockaddr_in server_addr;

  if(argc != 2){
    perror("please usage : <IPaddress>");
  }

  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(sock_fd < 0){ perror("socket error.\n"); exit(-1); }

  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family      = AF_INET;
  server_addr.sin_port        = htons(SERV_PORT);

  if(inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0){
    printf("inet_pton error for %s", argv[1]);
  }

  setnonblocking(sock_fd);

  struct timeval tm;
  tm.tv_sec   = 5;
  tm.tv_usec = 0;

  if(-1 != connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))){
    printf("connect success!\n");
    return -1;
  }
  if(errno == EINPROGRESS){
    printf("set nonblocking success!\n");
  }

  fd_set set;
  FD_ZERO(&set);
  FD_SET(sock_fd, &set);
  int maxfdp = sock_fd + 1;
  int error, sel;
  if( (sel = select(maxfdp, NULL, &set, NULL, &tm )) < 0){
    printf("select error!\n");
  }else if(sel == 0){
    printf("select timeout!\n");
  }else{
    int optlen = sizeof(int);
    if(getsockopt(sock_fd, SOL_SOCKET, SO_ERROR, &error, &optlen) < 0){
      printf("getsockopt error!\n");
      return -1;
    }
  }

  if(error == 0){
    send(sock_fd, "nonblocking socket", strlen("nonblocking socket") + 1, 0);
  }
  close(sock_fd);
  return 0;
}
