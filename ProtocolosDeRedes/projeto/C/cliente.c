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
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>

#include "extras/config.h"
#include "extras/md5.h"

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

  Arquivo file;
  strcpy(file.filename, "");

  Datagram segmento;

  char path[26 + BUFSIZE];
  strcpy(path, "/arquivos/udp/clientfiles/");

  int cpy, pacote, fd;

  while(1){
    // Nome do arquivo pra enviar
    if( strcmp(file.filename, "") == 0 ){
      printf("Digite o nome do arquivo: ");
      gets(file.filename);

      strcat(path, file.filename);

      // Abre o arquivo
      fd = open(path, O_RDONLY);

      // Determina tamanho do arquivo
      file.filesize = lseek(fd, 0, SEEK_END) + 1;
      lseek(fd, 0, SEEK_SET);

      // Envia os dados do arquivo
      sendto(clientSocket,(struct Arquivo*)&file,sizeof(file),0,(struct sockaddr *)&serverAddr,addr_size);
    }

    // Enviando partes do arquivo
    if( strcmp(file.filename, "") != 0 ){
      // Enviando partes do arquivo
      segmento.code = 1;
      strcpy(segmento.checksum, "202cb962ac59075b964b07152d234b70");
      // Enquanto ler do arquivo...
      while( (cpy = read(fd,segmento.data,BUFSIZE-1)) > 0 ){
        segmento.data[cpy] = '\0';
        segmento.size = strlen(segmento.data);
        // Enviar para o servidor
        sendto(clientSocket,(struct Datagram*)&segmento,sizeof(segmento),0,(struct sockaddr *)&serverAddr,addr_size);
        // Incrementa contador
        segmento.code++;
        // Limpa buffer
        strcpy(segmento.data, "");
      }
      // Encerrando leitura do arquivo
      close(fd);

      // Datagrama encerrando envio
      strcpy(segmento.data, "END");
      sendto(clientSocket,(struct Datagram*)&segmento,sizeof(segmento),0,(struct sockaddr *)&serverAddr,addr_size);

      // Limpando nome do arquivo
      strcpy(file.filename, "");
      strcpy(path, "/arquivos/udp/clientfiles/");
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