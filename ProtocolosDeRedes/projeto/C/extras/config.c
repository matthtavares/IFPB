/**
 * Programa criado como projeto de conclusão para
 * a disciplina de Protocolos de Redes do IFPB.
 *
 * Este é o código que contém os dados de configurações para conexão.
 *
 * https://github.com/matthtavares/IFPB/tree/master/ProtocolosDeRedes/projeto
 *
 * @author  Mateus Tavares  <mateus460@gmail.com>
 * @author  Ronily Gomes  <ronilyweb@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "md5.h"
#include "config.h"

void presentation(){
	system("clear");
	printf("\t\t\t----- DATAGRAM TCP -----\n\n");
	printf("\t\t\tWelcome to DATAGRAM TCP!\n\n");
	printf("      This is a program to simulate a TCP / IP transfer using a UDP socket.\n");
	printf("       All data is processed and sent using a client-server connection and\n");
	printf("    has everything needed for a great performance and correct transfer data.");
	printf("\n\n");
}

int checkmd5(char data[], char md5original[]){
	char newmd5[33];
	md5(data, newmd5);
	if( strcmp(md5original, newmd5) == 0 ) return 0;
	return 1;
}