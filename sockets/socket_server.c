/*Dependencias necessárias*/
 
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
 
int main()
{
    
    char str[100];

    /*
    * File Descriptors a serem utilizados
    */
    int listen_fd, comm_fd;

    /*
    * Estruturas para armazenar o endereço de IP
    * e as portas.
    */ 
    struct sockaddr_in servaddr;

    /*
    * Cada servidor precisa "ficar escutando" as conexões.
    * A função abaixo cria um socket com endereçamento de IP (AF_INET)
    * do tipo SOCKET_STREAM.
    *
    * Os dados dosd dispositivos tentando conectar à esse socket
    * será redirecionado à variável listen_fd.
    */
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    /*
    * Limpa o conteúdo que está no endereço de
    * servaddr (obrigatório).
    */
    bzero( &servaddr, sizeof(servaddr));
 
    //fala que o tipo de endereçamento é IP
    servaddr.sin_family = AF_INET;

    //Permite qualquer IP se conectar
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);

    //Escuta na porta 22000
    servaddr.sin_port = htons(22000);
 
    /*
    * prepara para escutar conexões de qualquer endereço/porta
    * especificado no sockaddr (qualquer ip na porta 22000)
    */
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 
    /*
    * começa a escutar as conexões mantendo no máximo 10
    * requests de conexão esperando.
    *
    * Se tiver mais de 10 computadores tentando conectar,
    * o 11 falhará.
    */
    listen(listen_fd, 10);
 
    /*
    * Aceita uma conexão de qualquer dispositivo tentando se conectar
    * Qualquer coisa enviada pelo dispositivo conectado pode ser lido
    * a partir de comm_fd, e qualquer coisa escrita em comm_fd é 
    * enviada para o outro dispositivo.
    */
    comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);


    /*
    * limpa a str, lê até 100 bytes nela e printa seu conteúdo.
    */
    while(1)
    {
 
        bzero( str, 100);
 
        read(comm_fd,str,100);
 
        printf("Recebido: %s", str);
 
        write(comm_fd, str, strlen(str)+1);
 
    }
}
