#include "unp.h"

void str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE];

	while (fgets(sendline, MAXLINE, fp) != NULL) {
		write(sockfd, sendline, strlen(sendline));
		if (read(sockfd, recvline, MAXLINE) == 0) 
			printf("str_cli: server terminated prematurely");
		fputs(recvline, stdout);
	}
}

int main(int argc, const char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;
	if (argc != 2)
		printf("usage: tcpcli <IPaddress>");

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
	str_cli((FILE *)stdin, sockfd);
	exit(0);
}
