/**
 * Programa para cópia de conteúdo de um arquivo em outro.
 *
 * https://github.com/matthtavares/IFPB/tree/master/SO/desafio-1
 *
 * @author  Mateus Tavares <mateus460@gmail.com>
 * @date    10/20/2016
 */

#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 100

void cpystr(char *txt, char *txt2);
int cmpstr(char *txt, char *txt2);
void clearLog();

int main (){
	char buffer[BUFSIZE];
	char filename[100], filename2[100];
	int fd, fd1;

	clearLog(); // Limpa tela

	write(1, "Nome do arquivo para copia: ", 28);
	read(1, buffer, BUFSIZE); // Ler entrada do usuario

	/* Copia e ajusta valor do buffer para vetor 'filename' */
	cpystr(buffer, filename);

	/* Abre o arquivo, printa erro caso não exista */
	fd = open(filename, O_RDONLY);
	while( fd < 0 ) {
		write(1, "Impossivel abrir o arquivo!\n\n", 29);

		write(1, "Nome do arquivo para copia: ", 28);
		read(1, buffer, BUFSIZE); // Ler entrada do usuario
		/* Copia e ajusta valor do buffer para vetor 'filename' */
		cpystr(buffer, filename);
		fd = open(filename, O_RDONLY);
	}

	write(1, "Nome do arquivo final: ", 23);
	read(1, buffer, BUFSIZE); // Ler entrada do usuario

	/* Copia e ajusta valor do buffer para vetor 'filename2' */
	cpystr(buffer, filename2);

	/* Verifica se os dois arquivos são diferentes */
	while( cmpstr(filename, filename2) == 1 ){
		write(1, "Voce nao pode utilizar o mesmo arquivo como origem e destino!\n\n", 63);

		write(1, "Nome do arquivo final: ", 23);
		read(1, buffer, BUFSIZE); // Ler entrada do usuario
		/* Copia e ajusta valor do buffer para vetor 'filename2' */
		cpystr(buffer, filename2);
	}

	/* Abre o arquivo, printa erro caso não seja possivel */
	fd1 = open(filename2, O_CREAT | O_EXCL | O_WRONLY, 0640);
	while( fd1 < 0 ){
		write(1, "O arquivo já existe!\n\n", 22);

		write(1, "Nome do arquivo final: ", 23);
		read(1, buffer, BUFSIZE); // Ler entrada do usuario
		/* Copia e ajusta valor do buffer para vetor 'filename2' */
		cpystr(buffer, filename2);
		fd1 = open(filename2, O_CREAT | O_EXCL | O_WRONLY, 0640);
	}

	/* Copia o arquivo */
	int cpy;
	while( cpy = read(fd,buffer,BUFSIZE) ){
		write(fd1,buffer,cpy);
	}

	/* Encerra buffer de leitura dos arquivos */
	close(fd);
	close(fd1);

	write(1, "\nArquivo copiado com sucesso!\n\n", 31);

	return 0;
}

/* Copia string */
void cpystr(char *txt, char *txt2){
	int i;
	for(i = 0; txt[i] != '\n'; ++i ){
		txt2[i] = txt[i];
	}
	txt2[i] = '\0';
}

/* Compara duas strings, 1 = Iguais, 0 = Diferentes */
int cmpstr(char txt[], char txt2[]){
	int i;
	for(i = 0; txt[i] != '\0' && txt2[i] != '\0'; ++i ){
		if( txt2[i] != txt[i] ) return 0;
	}
	return 1;
}

/* Limpar tela */
void clearLog(){
	const char* CLEAR_SCREE_ANSI = "\e[1;1H\e[2J";
	write(STDOUT_FILENO,CLEAR_SCREE_ANSI,11);
}