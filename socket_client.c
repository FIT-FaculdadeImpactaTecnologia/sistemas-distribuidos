#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
 
int main(int argc,char **argv)
{
    //file descriptor
    int sockfd, n;

    //linha enviada
    char sendline[100];

    //linha recebida
    char recvline[100];

    struct sockaddr_in servaddr;
 
    sockfd =socket(AF_INET,SOCK_STREAM, 0);
    bzero(&servaddr, sizeof servaddr);
 
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);

    /*
    * coloca o ip no serveraddr para localhost
    * pelo nosso server também estar rodando na
    * nossa máquina. 
    */
    inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));
 
    /*
    * Conecta aos dispositivos que o ip e porta estão
    * especificados no servaddr.
    */
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
 
    /*
    * limpa o sendline e recvline
    * le a string de stdin para sendline
    * escreve a sendline no sockfd
    * le do file descriptor no srecvline
    * mostra o recvline
    */
    while(1)
    {
        bzero(sendline, 100);
        bzero(recvline, 100);
        fgets(sendline, 100, stdin); /*stdin = 0 , for standard input */
 
        write(sockfd, sendline, strlen(sendline)+1);
        read(sockfd, recvline, 100);
        printf("%s", recvline);
    }
 
}