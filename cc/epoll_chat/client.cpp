#include "utility.h"

int main(int argc, char **argv)
{
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = PF_INET;
  serverAddr.sin_port = htons(SERVER_PORT);
  serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

  int sock = socket(PF_INET, SOCK_STREAM, 0);
  if(sock < 0){ perror("socket failed!\n"); exit(-1); }
  if( connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) <0 ){
    perror("connect failed!\n");
    exit(-1);
  }

  //pipeline : fd[0] : parent process read; fd[1] child process write
  int pipe_fd[2];
  if(pipe(pipe_fd) < 0) { perror("pipe failed!\n"); exit(-1); }

  //create epoll
  int epfd = epoll_create(EPOLL_SIZE);
  if(epfd < 0) { perror("epfd failed!\n"); exit(-1); }
  static struct epoll_event events[2];
  addfd(epfd, sock, true);
  addfd(epfd, pipe_fd[0], true);

  bool isClientwork = true;

  char message[BUF_SIZE];

  //fork
  int pid = fork();
  if( pid < 0 ) { perror("fork failed!\n"); exit(-1); }
  else if( pid == 0 ){
    //child process write,close read pipeline
    close(pipe_fd[0]);
    printf("Please input 'exit' to exit the chat room.\n");

    while(isClientwork){
      bzero(&message, BUF_SIZE);
      fgets(message, BUF_SIZE, stdin);

      if(strncasecmp(message, EXIT, strlen(EXIT)) == 0){
        isClientwork = 0;
      }
      else{//write message to pipeline
        if(write(pipe_fd[1], message, strlen(message) - 1) < 0){
          perror("write failed!\n");
          exit(-1);
        }
      }
    }
  }else{// pid > 0 : parent process
    //parent process read, close write pipeline
    close(pipe_fd[1]);

    while(isClientwork){
      int epoll_events_count = epoll_wait(epfd, events, 2, -1);
      //handle
      for(int i = 0; i < epoll_events_count; ++i)
      {
        bzero(&message, BUF_SIZE);
        if(events[i].data.fd == sock){
          //recv message
          int ret = recv(sock, message, BUF_SIZE, 0);

          if(ret == 0){
            printf("Server closed connection : %d\n", sock);
            close(sock);
            isClientwork = 0;
          }else 
            printf("%s\n",message);
        }else{
          int ret = read(events[i].data.fd, message, BUF_SIZE);
          if(ret == 0) isClientwork = 0;
          else{
            send(sock, message, BUF_SIZE, 0);
          }
        }
        
      }//for
    }//while
  }
  if(pid){
    //close pprocess and sock
    close(pipe_fd[0]);
    close(sock);
  }else{
    close(pipe_fd[1]);
  }
  return 0;
}
