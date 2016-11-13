/**
 * Programa criado como projeto de conclusão para
 * a disciplina de Protocolos de Redes do IFPB.
 *
 * Este é o código do cliente UDP que irá encaminhar
 * os datagramas.
 *
 * https://github.com/matthtavares/IFPB/tree/master/ProtocolosDeRedes/projeto
 *
 * @author  Mateus Tavares  <mateus460@gmail.com>
 * @author  Ronily Gomes  <ronilyweb@gmail.com>
 */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>

#include "config.h"

int main(){
  int clientSocket, portNum, nBytes;
  char buffer[BUFSIZE];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*Create UDP socket*/
  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(SERVICE_PORT);
  serverAddr.sin_addr.s_addr = inet_addr(SERVICE_HOST);
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverAddr;

  presentation();

  /* Estabelecendo conexão */
  printf("## TESTING CONNECTION...\n\n");
  int count = 1;
  int sendTo;
  while( count <= 3 ){
    printf("Connecting... ");

    strcpy(buffer, "HSK");
    nBytes = strlen(buffer) + 1;

    // Envia requisição
    sendTo = sendto(clientSocket, buffer, nBytes, 0, (struct sockaddr *)&serverAddr, addr_size);

    if( sendTo > 0 ){
      nBytes = recvfrom(clientSocket,buffer,BUFSIZE,0,NULL, NULL);

      if( nBytes > 0 && strcmp(buffer, "ACK") == 0 ){
        printf("OK.\n");
        count++;
      }else{
        printf("Error.\n");
        return 1;
      }
    }else{
      printf("Error.\n");
      return 1;
    }
  }

  printf("\n## STARTING TANSMISSION:\n\n");

  char arquivo[BUFSIZE];
  strcpy(arquivo, "");
  int cpy, fd;
  int fsize;
  char filesize[BUFSIZE];

  while(1){
    // Nome do arquivo pra enviar
    if( strcmp(arquivo, "") == 0 ){
      printf("Digite o nome do arquivo: ");
      gets(arquivo);

      // Envia nome do arquivo pra criar no servidor
      nBytes = strlen(arquivo) + 1;
      sendto(clientSocket,arquivo,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);

      fd = open(arquivo, O_RDONLY);

      // Determina tamanho do arquivo
      fsize = lseek(fd, 0, SEEK_END);
      lseek(fd, 0, SEEK_SET);
      sprintf(filesize, "%d", fsize);

      // Envia o tamanho do arquivo
      nBytes = sizeof(filesize) + 1;
      sendto(clientSocket,filesize,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);
    }

    // Enviando partes do arquivo
    if( strcmp(arquivo, "") != 0 ){
      // Enquanto ler do arquivo...
      while( cpy = read(fd,buffer,BUFSIZE) ){
        // Enviar para o servidor
        sendto(clientSocket,buffer,cpy,0,(struct sockaddr *)&serverAddr,addr_size);
      }
      close(fd);
      strcpy(arquivo, "");

      strcpy(buffer, "END");
      nBytes = strlen(buffer) + 1;
      sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);
    }


    // printf("Type a sentence to send to server:\n");
    // fgets(buffer,BUFSIZE,stdin);
    // printf("You typed: %s",buffer);

    // nBytes = strlen(buffer) + 1;
    
    // /*Send message to server*/
    // sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);

    // /*Receive message from server*/
    // nBytes = recvfrom(clientSocket,buffer,BUFSIZE,0,NULL, NULL);

    // printf("Received from server: %s\n",buffer);
  }

  return 0;
}