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
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>

#include "extras/config.h"
#include "extras/md5.h"

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

  Arquivo *file = malloc(sizeof(Arquivo));
  strcpy(file->filename, "");

  Datagram *segmento = malloc(sizeof(Datagram));

  char path[26 + BUFSIZE];
  strcpy(path, "/arquivos/udp/serverfiles/");

  int cpy, fd1;

  while(1){
    // Verifica se existe arquivo sendo recebido
    if( strcmp(file->filename, "") == 0 ){

      // Recebe os dados da struct
      recvfrom(udpSocket,file,sizeof(*file),0,(struct sockaddr *)&serverStorage, &addr_size);

      printf("Recebendo o arquivo: %s\n", file->filename);
      printf("Tamanho: %d bytes\n\n", file->filesize);

      strcat(path, file->filename);
      fd1 = open(path, O_CREAT | O_EXCL | O_WRONLY, 0640);
    }

    // Recebendo partes do arquivo
    if( strcmp(file->filename, "") != 0 ){
      // Recebendo parte do arquivo
      while( recvfrom(udpSocket,segmento,sizeof(*segmento),0,(struct sockaddr *)&serverStorage, &addr_size) ){
        if( strcmp(segmento->data, "END") == 0 ) break;
        else{
          // write(fd1, segmento->data, strlen(segmento->data)); // FUNCIONA!
          write(fd1, segmento->data, segmento->size);
        }
      }
      close(fd1);

      strcpy(file->filename, "");
      strcpy(path, "/arquivos/udp/serverfiles/");
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