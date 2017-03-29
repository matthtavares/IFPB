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
  if( arvoreVazia(*arv) )
    return NULL;

  if( (*arv)->info == dado ){
    return &(*arv);
  }

  if( dado < (*arv)->info )
    return busca(&(*arv)->esq, dado);
  else
    return busca(&(*arv)->dir, dado);
}

int remover(tab *arv, telem dado){
  tab p;

  if( arvoreVazia(*arv) )
    return 0;

  tab *novo;
  novo = busca(arv, dado);

  // Se n�o tiver filhos
  if( (*novo)->esq == NULL && (*novo)->dir == NULL ){
    free((*novo));
    *novo = NULL;
    return 1;
  }

  // Se n�o houver filhos � esquerda
  if( (*novo)->esq == NULL ){
    p = (*novo)->dir;
    free((*novo));
    *novo = p;
    return 1;
  }

  // Se n�o houver filhos � direita
  if( (*novo)->dir == NULL ){
    p = (*novo)->esq;
    free((*novo));
    *novo = p;
    return 1;
  }

  // Se houver filhos em ambos os n�s
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

void posOrdem(tab arv){
  if( arvoreVazia(arv) )
    return;

  if( arv->esq != NULL )
    posOrdem(arv->esq);

  if( arv->dir != NULL )
    posOrdem(arv->dir);

  printf("%c", arv->info);
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
 * Verifica se a pilha est� vazia.
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

void imprimePilhaLinha(pilha p){
	while( p != NULL ){
		printf("%c", (*p).leaf->info);
		p = p->prox;
	}
}

void esvaziarPilha(pilha *p){
    tab arv;
    while( *p != NULL ){
        desempilhar(p, &arv);
    }
    free(p);
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
 * Fun��es do projeto.
 */
/**
 * JA FUNCIONA PORRA!
 */
/*char* obterOperandos(char *expressao){
	pilha p;
	criaPilha(&p);

	char *ret = (char*)malloc(sizeof(char*) * strlen(expressao));
	int i = 0;

	char *aux;
	aux = expressao;
	while( *aux != '\0' ){
		if( *aux >= 'A' && *aux <= 'Z' ){
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
}*/

/**
 * A prioridade varia, conforme o s�mbolo se encontre na entrada ou no topo da pilha, de acordo com a seguinte tabela:
 *
 * +-----------+---------+----------+
 * |  SIMBOLO  |  PILHA  | ENTRADA  |
 * +-----------+---------+----------+
 * |     ^     |    3    |     4    |
 * +-----------+---------+----------+
 * |    * /    |    2    |     2    |
 * +-----------+---------+----------+
 * |    + -    |    1    |     1    |
 * +-----------+---------+----------+
 * |     (     |    0    |     4    |
 * +-----------+---------+----------+
 *
 * Fonte: http://www.vision.ime.usp.br/~pmiranda/mac122_2s14/aulas/aula13/aula13.html
 */
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
	tab desempilha, opr, novo, aux, arv;
	char c, t;
	int priori;

	criarArvore(&aux);
	criarArvore(&arv);

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

					inserir(&aux, desempilha->info);
					desempilhar(&saida, &desempilha);
					aux->dir = desempilha;
					desempilhar(&saida, &desempilha);
					aux->esq = desempilha;

					empilhar(&saida, &aux);
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

	while( desempilhar(&operadores, &desempilha) ){
		empilhar(&saida, &desempilha);
	}

	printf("Saida:\n");
	imprimePilha(saida);
	printf("Operadores:\n");
	imprimePilha(operadores);
	printf("\n\n");


	if( pilhaTamanho(saida) > 1 ){
		while( desempilhar(&saida, &desempilha) ){
			inserir(&arv, desempilha->info);

			desempilhar(&saida, &desempilha);
			arv->dir = desempilha;
			desempilhar(&saida, &desempilha);
			arv->esq = desempilha;
		}
	} else {
		desempilhar(&saida, &desempilha);
		arv = desempilha;
	}
	printf("Pos-ordem: ");
	posOrdem(arv);
	printf("\n\n");

	return NULL;
}
