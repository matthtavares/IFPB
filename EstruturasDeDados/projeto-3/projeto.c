#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include "projeto.h"

typedef struct stnopilha{
    char dado;
    struct stnopilha* prox;
} nop;
typedef struct {
	nop *inicio;
	int tam;
} pilha;

/**
 * Retorna o endereço para uma nova pilha.
 */
pilha* criaPilha(){
    pilha *p;
    p = (pilha*)malloc(sizeof(pilha*));
    return p;
}

/**
 * Verifica se a pilha está vazia.
 *
 * @param   pilha   p
 *
 * @return  int  0 = FALSE, 1 = TRUE
 */
int pilhaVazia(pilha p){
	return (p.tam == 0);
}

/**
 * Verifica o tamanho da pilha.
 *
 * @param   pilha   p
 *
 * @return  int
 */ 
int pilhaTamanho(pilha p){
	return p.tam;
}

/**
 * Inserir dado na pilha.
 *
 * @param   pilha   *p
 * @param   char    valor
 *
 * @return  int     0 = ERROR, 1 = SUCCESS
 */
int empilhar(pilha *p, char valor){
	nop *novo;
	novo = (nop*)malloc(sizeof(nop*));

	if( novo == NULL )
		return 0;

	novo->dado = valor;
	novo->prox = p->inicio;
	p->inicio = novo;

	p->tam++;

	return 1;
}

/**
 * Remover dado da pilha.
 *
 * @param   pilha   *p
 * @param   char    *valor
 *
 * @return  int     0 = ERROR, 1 = SUCCESS
 */
int desempilha(pilha *p, char *valor){
	if( pilhaVazia(*p) )
		return 0;

	nop *aux;
	aux = p->inicio;
	*valor = aux->dado;
	p->inicio = aux->prox;

	free(aux);

	p->tam--;

	return 1;
}

/**
 * Remove todos os itens da pilha.
 *
 * @param   pilha   *p
 *
 * @return  int     0 = ERROR, 1 = SUCCESS
 */
int esvaziarPilha(pilha *p){
	if( pilhaVazia(*p) )
		return 0;

	nop *aux;
	aux = p->inicio;

	while( aux != NULL ){
		p->inicio = aux->prox;
		free(aux);
		aux = p->inicio;
		p->tam--;
	}

	free(p);

	return 1;
}

/**
 * Busca um dado na pilha.
 *
 * @return  int     0 = ERROR, 1 = SUCCESS
 */
int buscaPilha(pilha p, char dado){
	nop *aux = p.inicio;
	while( aux != NULL ){
		if( dado == aux->dado ){
			return 1;
		}
		aux = aux->prox;
	}
	return 0;
}

/**
 * Imprime pilha.
 *
 * @param   pilha   p
 */
void imprimePilha(pilha p){
	int i = 1;
	nop *aux = p.inicio;
	while( aux != NULL ){
		printf("Valor %d = %c\n", i, aux->dado);
		aux = aux->prox;
		i++;
	}
}


/**
 * Cria uma arvore.
 */
tab* criaArvore(){
	tab *arv;
	arv = (tab*)malloc(sizeof(tab*));
	return arv;
}




int expressaoInfixaValida( char *expressao ){
	char *aux;
	aux = expressao;
	while( *aux != '\0' ){
		if( *aux < 65 && *aux > 90 && *aux != '/' && *aux != '*' && *aux != '+' && *aux != '-' && *aux != '(' && *aux != ')' && *aux != '^' ){
			return 0;
		}
		aux++;
	}
	return 1;
}

tab* converteInfixaParaArvore(char *expressao, int mostrarExecucao){
	tab *arvore;
	pilha *p;
	char *aux;

	p = criaPilha();

	if( (arvore = criaArvore()) == NULL )
		return NULL;

	aux = expressao;
	while( *aux != '\0' ){
		empilhar(p, *aux);
		aux++;
	}

	imprimePilha(*p);

	while( desempilha(p, aux) ){
		// Insere na árvore
	}

	esvaziarPilha(p);
	return arvore;
}

/**
 * JA FUNCIONA PORRA!
 */
char* obterOperandos(char *expressao){
	pilha *p;
	p = criaPilha();

	char *ret = (char*)malloc(sizeof(char*) * strlen(expressao));
	int i = 0;

	char *aux;
	aux = expressao;
	while( *aux != '\0' ){
		if( *aux >= 65 && *aux <= 90 ){
			if( !buscaPilha(*p, *aux) ){
				empilhar(p, *aux);
				ret[i] = *aux;
				i++;
			}
		}
		aux++;
	}
	ret[i] = '\0';

	esvaziarPilha(p);
	return ret;
}