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
#define BUFSIZE 500

typedef struct {
	int filesize;
	char filename[BUFSIZE];
} Arquivo;

typedef struct {
	int code;
	int size;
	char data[BUFSIZE];
	char checksum[33];
} Datagram;

void presentation();