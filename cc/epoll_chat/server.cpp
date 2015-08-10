#include "utility.h"

int main(int argc, char **argv)
{
  //server IP + port
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = PF_INET;
  serverAddr.sin_port = htons(SERVER_PORT);
  serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

  //create socket
  int listener = socket(PF_INET, SOCK_STREAM, 0);
  if(listener < 0) { perror("socket failed!"); exit(-1); }

  if( bind(listener, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0 ){
    perror("bind failed!\n");
    exit(-1);
  }

  //listen
  int ret = listen(listener, 5);
  if( ret < 0 ){ perror("listen failed!\n"); exit(-1); }
  printf("Start to listen : %s\n", SERVER_IP);
  
  int epfd = epoll_create(EPOLL_SIZE);
  if(epfd < 0){ perror("epfd failed\n"); exit(-1); }
  printf("epoll created, epollfd = %d\n", epfd);
  static struct epoll_event events[EPOLL_SIZE];

  addfd(epfd, listener, true);

  while(1)
  {
    int epoll_events_count = epoll_wait(epfd, events, EPOLL_SIZE, -1);
    if( epoll_events_count < 0 ){
      perror("epoll failure!\n");
      break;
    }

    printf("epoll_events_count = %d\n",epoll_events_count);

    for(int i = 0; i < epoll_events_count; ++i)
    {
      int sockfd = events[i].data.fd;

      if(sockfd == listener)
      {
        struct sockaddr_in client_address;
        socklen_t client_addrLength = sizeof(struct sockaddr_in);
        //new user accepted
        int clientfd = accept(listener, (struct sockaddr *)&client_address, &client_addrLength);
        printf("client connection from : %s : %d(IP : port), clientfd = %d \n",inet_ntoa(client_address.sin_addr),
            ntohs(client_address.sin_port),
            clientfd);

        addfd(epfd, clientfd, true);

        //server use list save user's connection
        clients_list.push_back(clientfd);
        printf("Add new clientfd = %d to epoll\n", clientfd);
        printf("Now there are %d clients int the chat room\n",(int)clients_list.size());

        //server send welcome
        printf("welcome message\n");
        char message[BUF_SIZE];
        bzero(message, BUF_SIZE);
        sprintf(message, SERVER_WELCOME, clientfd);
        int ret = send(clientfd, message, BUF_SIZE, 0);
        if( ret < 0 ) { perror("send failed!\n"); exit(-1); }
      }else{
        int ret = sendBroadcastmessage(sockfd);
        if( ret < 0 ) { perror("send broadcast failed!\n"); exit(-1); }
      }
    }
  }
  close(listener);//close socket
  close(epfd);    //close kernel
  return 0;
}
