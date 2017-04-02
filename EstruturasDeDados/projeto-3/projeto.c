#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "projeto.h"

void criarArvore(tab *arv){
    *arv = NULL;
}

int arvoreVazia(tab arv){
    return (arv == NULL);
}

int inserir(tab *arv, telem dado){
  tno *novo;
  tno *p = *arv;

  if( arvoreVazia(*arv) ){
    if( (novo = (tno*)malloc(sizeof(tno))) == NULL )
      return 0;

    novo->info = dado;
    novo->esq = novo->dir = NULL;

    *arv = novo;

    return 1;
  } else if( dado < p->info ) {
    return inserir(&p->esq, dado);
  } else if( dado > p->info ) {
    return inserir(&p->dir, dado);
  }

  return 0;
}

tab* busca(tab *arv, telem dado){
	tab *value;

	if( arvoreVazia(*arv) )
		return NULL;

	if( (*arv)->info == dado ){
		value = &(*arv);
	}

	if( value == NULL && (*arv)->esq != NULL  )
		value = busca(&(*arv)->esq, dado);
	else if( value == NULL && (*arv)->dir != NULL )
		value = busca(&(*arv)->dir, dado);

	return value;
}

int remover(tab *arv, telem dado){
  tab p;

  if( arvoreVazia(*arv) )
    return 0;

  tab *novo;
  novo = busca(arv, dado);

  // Se não tiver filhos
  if( (*novo)->esq == NULL && (*novo)->dir == NULL ){
    free((*novo));
    *novo = NULL;
    return 1;
  }

  // Se não houver filhos à esquerda
  if( (*novo)->esq == NULL ){
    p = (*novo)->dir;
    free((*novo));
    *novo = p;
    return 1;
  }

  // Se não houver filhos à direita
  if( (*novo)->dir == NULL ){
    p = (*novo)->esq;
    free((*novo));
    *novo = p;
    return 1;
  }

  // Se houver filhos em ambos os nós
  tab *ultimo;
  ultimo = &(*novo)->esq;
  while( (*ultimo)->dir != NULL ){
    ultimo = &(*ultimo)->dir;
  }

  printf("No = %d\n", (*ultimo)->info);

  (*novo)->info = (*ultimo)->info;
  free(*ultimo);
  (*ultimo) = NULL;

  return 1;
}

void esvaziar(tab *arv){
  if( arvoreVazia(*arv) )
    return;

  esvaziar(&(*arv)->esq);
  esvaziar(&(*arv)->dir);

  free(*arv);

  *arv = NULL;
}

/**
 * Estrutura de pilha.
 */
typedef struct stno {
    tno *leaf;
    struct stno *prox;
} nop;

typedef nop* pilha;

void criarPilha(pilha *p){
    *p = NULL;
}

/**
 * Verifica se a pilha está vazia.
 *
 * @return  int  0 = FALSE, 1 = TRUE
 */
int pilhaVazia(pilha p){
	return (p == NULL);
}

/**
 * Verifica o tamanho da pilha.
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

int empilhar(pilha *p, tab *leaf){
	nop *novo;
	novo = (nop*)malloc(sizeof(nop*));

	if( novo == NULL )
		return 0;

	novo->leaf = *leaf;
	novo->prox = *p;
	*p = novo;

	return 1;
}

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

int topo(pilha p, tab *arv){
	if( pilhaVazia(p) )
		return 0;

	*arv = (*p).leaf;

	return 1;
}

void imprimePilha(pilha p){
	while( p != NULL ){
		printf("- %c\n", (*p).leaf->info);
		p = p->prox;
	}
}

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
 * FUNÇÕES DO PROJETO!
 */

char* obterOperandos(char *expressao){
	pilha p;
	tab arv;
	criarPilha(&p);

	char *ret = (char*)malloc(sizeof(char*) * strlen(expressao));
	int i = 0;

	char *aux;
	aux = expressao;
	while( *aux != '\0' ){
		if( *aux >= 'A' && *aux <= 'Z' ){
			if( !buscaPilha(p, *aux) ){
        		criarArvore(&arv);
        		inserir(&arv, *aux);

				empilhar(&p, &arv);
				ret[i++] = *aux;
			}
		}
		aux++;
	}
	ret[i] = '\0';

	esvaziarPilha(&p);
	return ret;
}

char* obterExpressaoPosfixa(tab *T){
	if( arvoreVazia(*T) )
		return NULL;

	char *ret = (char*)malloc(sizeof(char*));
	char *cat = (char*)malloc(sizeof(char*));
	strcpy(ret, "");

	if( (*T)->esq != NULL ){
		sprintf(cat, "%s", obterExpressaoPosfixa(&(*T)->esq));
		strcat(ret, cat);
	}

	if( (*T)->dir != NULL ){
		sprintf(cat, "%s", obterExpressaoPosfixa(&(*T)->dir));
		strcat(ret, cat);
	}

	sprintf(cat, "%c", (*T)->info);
	strcat(ret, cat);

	return ret;
}

int prioridade(char e){
	switch( e ){
		case '(':
			return 1;
		case '+':
		case '-':
			return 2;
		case '*':
		case '/':
			return 3;
		case '^':
			return 4;
	}
}

tab* converteInfixaParaArvore(char *expressao, int mostrarExecucao){
	pilha operadores, saida;
	tab desempilha, opr, novo, *arv;
	char c;
	int priori;

	criarPilha(&operadores);
	criarPilha(&saida);

	while( *expressao != '\0' ){
		c = *expressao;
		if( c >= 'A' && c <= 'Z' ){
			criarArvore(&novo);
			inserir(&novo, c);
			empilhar(&saida, &novo);
		}else if( c == '(' ){
			criarArvore(&novo);
			inserir(&novo, c);
			empilhar(&operadores, &novo);
		}else if( c == ')' ){
			do{
				desempilhar(&operadores, &opr);
				if( opr->info != '(' ){
					desempilhar(&saida, &opr->dir);
					desempilhar(&saida, &opr->esq);
					empilhar(&saida, &opr);
				}
			}while( opr->info != '(' );
		}else if( c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ){
			topo(operadores, &desempilha);
			priori = prioridade(c);
			while( 1 ){
				if( !pilhaVazia(operadores) && prioridade(desempilha->info) >= priori ){
					desempilhar(&operadores, &desempilha);

					desempilhar(&saida, &desempilha->dir);
					desempilhar(&saida, &desempilha->esq);
					empilhar(&saida, &desempilha);

					topo(operadores, &desempilha);
				} else {
					criarArvore(&novo);
					inserir(&novo, c);
					empilhar(&operadores, &novo);
					break;
				}
			}
		}
		expressao++;
	}

	// Esvazia pilha de operadores para saida
	while( desempilhar(&operadores, &desempilha) ){
		desempilhar(&saida, &desempilha->dir);
		desempilhar(&saida, &desempilha->esq);
		empilhar(&saida, &desempilha);
	}

	// Aloca a arvore
	arv = (tab*)malloc(sizeof(tab*));

	// Desempilha a saida para a arvore
	desempilhar(&saida, arv);

	return arv;
}

float executaExpressao(tab *T, char *operandos, float *valor){
	return 87985953.148975689;
}