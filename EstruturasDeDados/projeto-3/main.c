#include <stdio.h>
#include <string.h>
#include "projeto.h"

int main(){
	/*pilha *p;
	p = criaPilha();
	printf("Tamanho: %d\n", pilhaTamanho(*p));
	if( pilhaVazia(*p) )
		printf("Pilha vazia!\n");

	empilhar(p, 'a');
	empilhar(p, 'b');
	empilhar(p, 'c');
	imprimePilha(*p);
	printf("Tamanho: %d\n", pilhaTamanho(*p));


	char valor;
	desempilha(p, &valor);
	imprimePilha(*p);
	printf("Tamanho: %d\n", pilhaTamanho(*p));*/

	char infixa[50];
	tab arvore;

	gets(infixa);
	printf("%d\n", strlen(infixa));
	puts(infixa);

	char *texto = obterOperandos(infixa);
	printf("Texto = %s\n", texto);

	int valido = expressaoInfixaValida(infixa);
	printf("Valido = %d\n", valido);

	//converteInfixaParaArvore(infixa, 0);

	return 0;
}
