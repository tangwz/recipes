#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LISTEN_NUM 1024
/*
 * 协议无关的host_serv
 * 返回：若成功则为指向addrinfo结构的指针，失败则为NULL
 */
struct addrinfo* 
host_serv(const char* host, const char* serv, int family, int socktype)
{
	int n;
	struct addrinfo hints, *res;
	
	bzero(&hints, sizeof(struct  addrinfo));
	hints.ai_flags    = AI_CANONNAME; //always return canonnical name
	hints.ai_family   = family;       //AF_UNSPEC, AF_INET, AF_INET6, etc
	hints.ai_socktype = socktype;     //0, SOCK_STREAM, SOCK_DGRAM, etc

	if( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
		return NULL;

	return res;
};

/*
 * 协议无关的tcp connect
 * 返回：成功则为已连接套接字描述符，若出错则不返回
 */
int tcp_connect(const char* host, const char* serv)
{
	int sockfd, n;
	struct addrinfo hints, *res, *ressave;

	bzero(&hints, sizeof(struct  addrinfo));
	hints.ai_family   = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
		fprintf(stderr, "tcp_connect error for %s, %s: %s\n",host, serv,
				gai_strerror(n) );
	ressave = res;

	do
	{
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(sockfd < 0)
			continue; //ignore this one

		if(connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
			break;    //success

		close(sockfd);
	} while ( (res = res->ai_next) != NULL);

	if(res == NULL)
		fprintf(stderr, "tcp_connect error for %s, %s", host, serv);

	freeaddrinfo(ressave);

	return sockfd;
}

/*
 * 执行TCP服务器的常规步骤：
 * 1、创建一个TCP套接字
 * 2、给它捆绑服务器的众所周知端口
 * 3、允许接受外部来的连接请求
 * 返回：成功则为已连接套接字描述符， 若出错则不返回
 */
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
    fprintf(stderr, "tcp_listen() error for %s, %s: %s\n", host, serv, gai_strerror(n));
    exit(1);

  }
  ressave = res;
  do {
    listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (listenfd < 0)
      continue;      // error, try next one

    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
      fprintf(stderr, "tcp_listen() error: %s\n", strerror(errno));
      exit(1);
    }

    if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
      break;         //success

    close(listenfd); //bind error, close and try next one
  } while ((res = res->ai_next) != NULL);

  if (res == NULL) { //errno from final socket() or bind()
    fprintf(stderr, "tcp_listen() error for %s, %s", host, serv);
    exit(1);
  }

  if (listen(listenfd, LISTEN_NUM) < 0) {
    fprintf(stderr, "tcp_listen() error: %s\n", strerror(errno));
    exit(1);
  }

  if (addrlenp)
    *addrlenp = res->ai_addrlen;//return size of protocol address

  freeaddrinfo(ressave);

  return listenfd;
}