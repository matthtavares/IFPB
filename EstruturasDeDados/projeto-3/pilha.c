#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "pilha.h"

/**
 * Funcoes para criacao de pilhas para nos de arvores.
 */

/**
 * Inicializa a pilha de arvores.
 *
 * @param  pilha  *p  Endereço para pilha
 */
void criarPilha(pilha *p){
    *p = NULL;
}

/**
 * Verifica se a pilha está vazia.
 *
 * @param  pilha  p  Pilha a ser verificada
 *
 * @return  int  0 = FALSE, 1 = TRUE
 */
int pilhaVazia(pilha p){
	return (p == NULL);
}

/**
 * Verifica o tamanho da pilha.
 *
 * @param  pilha  p  Pilha a ser verificada
 *
 * @return  int
 */
int pilhaTamanho(pilha p){
	if( pilhaVazia(p) )
		return 0;

	int i = 0;
	while( p != NULL ){
		i++;
		p = p->prox;
	}

	return i;
}

/**
 * Insere dado na pilha.
 *
 * @param  pilha  *p     Pilha a ser modificada
 * @param  tab    *leaf  Endereço do nó de arvore para empilhar
 *
 * @return  int  1 = SUCCESS, 0 = ERROR
 */
int empilhar(pilha *p, tab *leaf){
	nop *novo;

	if( (novo = (nop*)malloc(sizeof(nop*))) == NULL )
		return 0;

	novo->leaf = *leaf;
	novo->prox = *p;
	*p = novo;

	return 1;
}

/**
 * Remove dado da pilha.
 *
 * @param  pilha  *p     Pilha a ser modificada
 * @param  tab    *arv   Endereço do nó de arvore que armazena o dado desempilhado
 *
 * @return  int  1 = SUCCESS, 0 = ERROR
 */
int desempilhar(pilha *p, tab *arv){
	if( pilhaVazia(*p) )
		return 0;

	nop *aux;
	aux = *p;
	*arv = aux->leaf;
	*p = aux->prox;

	free(aux);

	return 1;
}

/**
 * Pega o dado no topo da pilha.
 *
 * @param  pilha  p     Pilha a ser verificada
 * @param  tab    *arv  Endereço do nó de arvore que armazena o dado
 *
 * @return  int  1 = SUCCESS, 0 = ERROR
 */
int topo(pilha p, tab *arv){
	if( pilhaVazia(p) )
		return 0;

	*arv = (*p).leaf;

	return 1;
}

/**
 * Imprime todos os dados armazenados na pilha.
 *
 * @param  pilha  p     Pilha a ser verificada
 */
void imprimePilha(pilha p){
	while( p != NULL ){
		printf("- %c\n", (*p).leaf->info);
		p = p->prox;
	}
}

/**
 * Esvazia toda a pilha.
 *
 * @param  pilha  *p    Pilha a ser modificada
 */
void esvaziarPilha(pilha *p){
    tab arv;
    while( *p != NULL ){
        desempilhar(p, &arv);
    }
    *p = NULL;
}

/**
 * Busca um dado na pilha.
 *
 * @param  pilha  *p    Pilha a ser verificada
 * @param  telem  dado  Dado a ser procurado
 *
 * @return  int     0 = ERROR, 1 = SUCCESS
 */
int buscaPilha(pilha p, telem dado){
    tab aux;
 	while( p != NULL ){
        aux = p->leaf;
 		if( (*aux).info == dado ){
 			return 1;
 		}
 		p = p->prox;
 	}
 	return 0;
}


/**
 * Funcoes para criacao de pilhas para float.
 */

/**
 * Inicializa a pilha de float.
 *
 * @param  vpilha  *p  Endereço para pilha
 */
void criarIPilha(vpilha *p){
    *p = NULL;
}

/**
 * Verifica se a pilha está vazia.
 *
 * @param  vpilha  p  Pilha a ser verificada
 *
 * @return  int  0 = FALSE, 1 = TRUE
 */
int vpilhaVazia(vpilha p){
	return (p == NULL);
}

/**
 * Verifica o tamanho da pilha.
 *
 * @param  vpilha  p  Pilha a ser verificada
 *
 * @return  int
 */
int vpilhaTamanho(vpilha p){
	if( vpilhaVazia(p) )
		return 0;

	int i = 0;
	while( p != NULL ){
		i++;
		p = p->prox;
	}

	return i;
}

/**
 * Insere dado na pilha.
 *
 * @param  vpilha  *p     Pilha a ser modificada
 * @param  float   dado   Valor a ser empilhado
 *
 * @return  int  1 = SUCCESS, 0 = ERROR
 */
int empilharV(vpilha *p, float dado){
	nopv *novo;

	if( (novo = (nopv*)malloc(sizeof(nopv*))) == NULL )
		return 0;

	novo->dado = dado;
	novo->prox = *p;
	*p = novo;

	return 1;
}

/**
 * Remove dado da pilha.
 *
 * @param  vpilha  *p     Pilha a ser modificada
 * @param  float   *dado  Endereço da variável que armazena o dado desempilhado
 *
 * @return  int  1 = SUCCESS, 0 = ERROR
 */
int desempilharV(vpilha *p, float *dado){
	if( vpilhaVazia(*p) )
		return 0;

	nopv *aux;
	aux = *p;
	*dado = aux->dado;
	*p = aux->prox;

	free(aux);

	return 1;
}

/**
 * Pega o dado no topo da pilha.
 *
 * @param  vpilha  p      Pilha a ser verificada
 * @param  float   *dado  Endereço da variável que armazena o dado
 *
 * @return  int  1 = SUCCESS, 0 = ERROR
 */
int topoPilhaV(vpilha p, float *dado){
	if( vpilhaVazia(p) )
		return 0;

	*dado = (*p).dado;

	return 1;
}

/**
 * Imprime todos os dados armazenados na pilha.
 *
 * @param  vpilha  p     Pilha a ser verificada
 */
void imprimeVPilha(vpilha p){
	while( p != NULL ){
		printf("- %f\n", (*p).dado);
		p = p->prox;
	}
}

/**
 * Esvazia toda a pilha.
 *
 * @param  vpilha  *p    Pilha a ser modificada
 */
void esvaziarVPilha(vpilha *p){
    float dado;
    while( *p != NULL ){
        desempilharV(p, &dado);
    }
    *p = NULL;
}