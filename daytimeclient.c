#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
int main(int argc, int **argv)
{
	int listenfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr,chiladdr;
	char buff[100];
	time_t ticks;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htonl(13);
	bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
	listen(listenfd, LISTENQ);
	for( ; ;){
		len = sizeof(chiladdr);
		connfd = accept(listenfd, (SA *) &cliaddr, &len);
		printf("connection from %s, port %d\n",inet_ntop(AF_INET, &chiladdr.sin_addr, buff, sizeof(buff)),ntohs(chiladdr.sin_port));
		ticks = time(NULL);
		snprintf(buff,sizeof(buff),"%.24s\r\n", ctime(&ticks));
		write(connfd, buff, strlen(buff));
		close(connfd);
	}
}
