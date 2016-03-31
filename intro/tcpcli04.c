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
	int i, sockfd[5];
	struct sockaddr_in servaddr;
	if (argc != 2)
		printf("usage: tcpcli <IPaddress>");

	for (i = 0; i < 5; i++) {
		sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);

		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(SERV_PORT);
		inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
		connect(sockfd[i], (SA *) &servaddr, sizeof(servaddr));
	}
	str_cli((FILE *)stdin, sockfd[0]);
	exit(0);
}
