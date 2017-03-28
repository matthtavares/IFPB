#include <stdlib.h>
#include <malloc.h>

/* Define que a execução da transformação infixa em pós-
fixa será apresentada na tela */
#define MOSTRAR 1

/* Define que a execução da transformação da
expressão infixa em pós-fixa não será apresentada na tela */
#define NAO_MOSTRAR 0

/* tipo base dos elementos da árvore */
typedef char telem;

/* nó da árvore */
typedef struct no {
  struct no *esq;
  telem info;
  struct no *dir;
} tno;

/* ponteiro para a raiz da árvore */
typedef tno *tab;

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

int desempilhar(pilha *p, telem *valor){
	if( pilhaVazia(*p) )
		return 0;

	nop *aux;
	aux = *p;
	*valor = aux->leaf->info;
	*p = aux->prox;

    free(aux->leaf);
	free(aux);

	return 1;
}

int topo(pilha p, telem *valor){
	if( pilhaVazia(p) )
		return 0;

	*valor = (*p).leaf->info;

	return 1;
}

void imprimePilha(pilha p){
	while( p != NULL ){
		printf("%c\n", (*p).leaf->info);
		p = p->prox;
	}
}

void esvaziarPilha(pilha *p){
    telem *dado;
    while( *p != NULL ){
        desempilhar(p, dado);
    }
    free(p);
    *p = NULL;
}
