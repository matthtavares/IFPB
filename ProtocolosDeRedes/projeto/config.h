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

#define SERVICE_HOST "172.28.128.4"
#define SERVICE_PORT 60000
#define BUFSIZE 100

typedef struct {
	short int flag;
	short int segment;
	unsigned char checksum[20];
	char data[100];
} Datagram;

void presentation(){
	system("clear");
	printf("\t\t\t----- DATAGRAM TCP -----\n\n");
	printf("\t\t\tWelcome to DATAGRAM TCP!\n\n");
	printf("      This is a program to simulate a TCP / IP transfer using a UDP socket.\n");
	printf("       All data is processed and sent using a client-server connection and\n");
	printf("    has everything needed for a great performance and correct transfer data.");
	printf("\n\n");
}