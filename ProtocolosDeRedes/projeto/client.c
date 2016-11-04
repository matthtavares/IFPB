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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include "config.h" // Arquivo para configurações

#define MSGS 10

int main(){

	struct sockaddr_in myaddr; // Our address
	struct sockaddr_in remaddr; // Remote address
	int fd, i;
	int slen = sizeof(remaddr); // Destination length
	char buf[BUFSIZE]; // Message buffer
	int recvlen; // n bytes in ACK message

	/* CREATE A UDP SOCKET */
	// int socket(int domain, int type, int protocol);
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if( fd == -1 ){
		printf("ERRO AO CRIAR SOCKET!\n");
		return 1;
	}

	/* bind it to all local addresses and pick any port number */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = inet_addr(SERVICE_HOST);
	myaddr.sin_port = htons(0);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 0;
	}       

	/* now define remaddr, the address to whom we want to send messages */
	/* For convenience, the host address is expressed as a numeric IP address */
	/* that we will convert to a binary format via inet_aton */

	memset((char *) &remaddr, 0, sizeof(remaddr));
	remaddr.sin_family = AF_INET;
	remaddr.sin_port = htons(SERVICE_PORT);
	if (inet_aton(SERVICE_HOST, &remaddr.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	/* SEND MESSAGES */
	for ( i = 0; i < MSGS; i++) {
		printf("Sending packet %d to %s port %d\n", i, SERVICE_HOST, SERVICE_PORT);
		sprintf(buf, "Pacote %d", i); // mensagem que será enviada

		if ( sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, slen) == -1 ) {
			perror("sendto");
			exit(1);
		}

		/* RECEIVING A ACK MESSAGE FROM THE SERVER */
		recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &slen);

        if (recvlen >= 0) {
            buf[recvlen] = 0; // expect a printable string - terminate it
            printf("received message: \"%s\"\n", buf);
        }
	}

	close(fd); // Encerra socket

	return 0;

}
