#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUFSIZE 1024

int lenstr(char *txt);
void cpystr(char *txt, char *txt2);
int cmpstr(char *txt, char *txt2);
void clearLog();

int main (){
	char buffer[BUFSIZE];
	char filename[100], filename2[100];
	int fd, fd1;

	clearLog(); // Limpa tela

	write(0, "Nome do arquivo para copia: ", 28);
	read(0, buffer, BUFSIZE); // Ler entrada do usuario

	/* Copia e ajusta valor do buffer para vetor 'filename' */
	cpystr(buffer, filename);

	/* Abre o arquivo, printa erro caso não exista */
	if ( ( fd = open(filename, O_RDONLY) ) < 0 ) {
		write(0, "Impossivel abrir o arquivo!\n\n", 29);
		return 1;
	}

	write(0, "Nome do arquivo final: ", 23);
	read(0, buffer, BUFSIZE); // Ler entrada do usuario

	/* Copia e ajusta valor do buffer para vetor 'filename2' */
	cpystr(buffer, filename2);

	/* Verifica se os dois arquivos são diferentes */
	if( cmpstr(filename, filename2) == 1 ){
		write(0, "Voce nao pode utilizar o mesmo arquivo como origem e destino!\n\n", 63);
		return 1;
	}

	/* Abre o arquivo, printa erro caso não seja possivel */
	if( ( fd1 = open(filename2,O_CREAT | O_WRONLY,S_IRUSR) ) < 0 ){
		write(0, "O arquivo já existe!\n\n", 22);
		return 1;
	}

	/* Copia o arquivo */
	ssize_t cpy;
	while( cpy = read(fd,buffer,BUFSIZE) ){
		write(fd1,buffer,cpy);
	}

	/* Encerra buffer de leitura dos arquivos */
	close(fd);
	close(fd1);

	write(0, "\nArquivo copiado com sucesso!\n\n", 31);

	return 0;
}

/* Tamanho da string */
int lenstr(char *txt){
	int i;
	for( i = 0; txt[i] != '\0'; ++i );
	return i;
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
		if( txt2[i] == txt[i] ) return 1;
	}
	return 0;
}

/* Limpar tela */
void clearLog(){
	const char* CLEAR_SCREE_ANSI = "\e[1;1H\e[2J";
	write(STDOUT_FILENO,CLEAR_SCREE_ANSI,11);
}
