/**
 * Programa criado como projeto de conclusão para
 * a disciplina de Protocolos de Redes do IFPB.
 *
 * Este é o código do servidor UDP que irá receber
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
#include <stdlib.h>
#include <fcntl.h>

#include "config.h"

int main(){
  int udpSocket, nBytes;
  char buffer[BUFSIZE];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  int i;

  /*Create UDP socket*/
  udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(SERVICE_PORT);
  serverAddr.sin_addr.s_addr = inet_addr(SERVICE_HOST);
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*Bind socket with address struct*/
  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverStorage;

  presentation();

  // Para contar requisicoes de conexao
  printf("## AWAITING CONNECTION...\n\n");
  int requisicoes = 1;
  while( requisicoes <= 3 ){
    // Recebe envios do cliente
    recvfrom(udpSocket,buffer,BUFSIZE,0,(struct sockaddr *)&serverStorage, &addr_size);

    // Verifica buffer de recebimento
    if( strcmp(buffer, "HSK") == 0 ){
      strcpy(buffer, "ACK");
      
      nBytes = strlen(buffer) + 1;

      sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
      requisicoes++;
    }
  }

  // Verifica total de requisicoes
  if( requisicoes > 3 ){
    printf("Connection established!\nReady to begin transmission.");
  }else{
    return 1;
  }

  printf("\n\n## STARTING TANSMISSION:\n\n");

  char arquivo[BUFSIZE];
  strcpy(arquivo, "");
  char fsize[BUFSIZE];
  char* filecontent = NULL;

  char path[16 + BUFSIZE];
  strcpy(path, "");
  strcat(path, "/arquivos/files/");

  int cpy, fd1;

  while(1){
    // Recebe nome do arquivo
    if( strcmp(arquivo, "") == 0 ){
      recvfrom(udpSocket,arquivo,BUFSIZE,0,(struct sockaddr *)&serverStorage, &addr_size);
      printf("Recebendo o arquivo: %s\n", arquivo);

      recvfrom(udpSocket,fsize,BUFSIZE,0,(struct sockaddr *)&serverStorage, &addr_size);
      filecontent = (char*) malloc(sizeof(char) * atoi(fsize));
      printf("Tamanho: %s bytes\n", fsize);

      strcat(path, arquivo);
      fd1 = open(path, O_CREAT | O_EXCL | O_WRONLY, 0755);
    }

    // Recebendo partes do arquivo
    if( strcmp(arquivo, "") != 0 ){
      strcpy(filecontent, "");
      // Recebendo parte do arquivo
      while( recvfrom(udpSocket,buffer,BUFSIZE,0,(struct sockaddr *)&serverStorage, &addr_size) ){
        if( strcmp(buffer, "END") == 0 ) break;
        else strcat(filecontent, buffer);
      }
      write(fd1, filecontent, atoi(fsize));
      close(fd1);
      free(filecontent);

      strcpy(arquivo, "");
      strcpy(path, "");
      strcat(path, "/arquivos/files/");
    }
  


    /* Try to receive any incoming UDP datagram. Address and port of 
      requesting client will be stored on serverStorage variable */
    // nBytes = recvfrom(udpSocket,buffer,BUFSIZE,0,(struct sockaddr *)&serverStorage, &addr_size);

    // /* Printa mensagem */
    // printf("Message received: %s", buffer);

    // /*Convert message received to uppercase*/
    // for(i=0;i<nBytes-1;i++)
    //   buffer[i] = toupper(buffer[i]);

    // /* Printa mensagem */
    // printf("Message sent: %s\n", buffer);

    // /*Send uppercase message back to client, using serverStorage as the address*/
    // sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
  }

  return 0;
}