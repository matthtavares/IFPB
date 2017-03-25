#include <malloc.h>
#include <stdio.h>

typedef struct stno {
  struct stno* esq;
  int dado;
  struct stno* dir;
} no;

typedef no* arv;

void inicializa(arv *arvore){
  *arvore = NULL;
}

int vazia(arv arvore){
  return (arvore == NULL);
}

int inserir(arv *arvore, int dado){
  no *novo;
  no *p = *arvore;

  if( vazia(*arvore) ){
    if( (novo = (no*)malloc(sizeof(no))) == NULL )
      return 0;

    novo->dado = dado;
    novo->esq = novo->dir = NULL;

    *arvore = novo;

    return 1;
  } else if( dado < p->dado ) {
    return inserir(&p->esq, dado);
  } else if( dado > p->dado ) {
    return inserir(&p->dir, dado);
  }

  return 0;
}

/**
 * Busca no estilo pre-ordem.
 */
arv* busca(arv *arvore, int dado){
  if( vazia(*arvore) )
    return NULL;

  if( (*arvore)->dado == dado ){
    return &(*arvore);
  }

  if( dado < (*arvore)->dado )
    return busca(&(*arvore)->esq, dado);

  if( dado > (*arvore)->dado )
    return busca(&(*arvore)->dir, dado);
}

/**
 * Esvaziar no formato pos-ordem.
 */
void esvaziar(arv *arvore){
  if( vazia(*arvore) )
    return;

  esvaziar(&(*arvore)->esq);
  esvaziar(&(*arvore)->dir);

  free(*arvore);

  *arvore = NULL;
}


int remover(arv *arvore, int dado){
  arv p;

  if( vazia(*arvore) )
    return 0;

  arv *novo;
  novo = busca(arvore, dado);

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
  arv *ultimo;
  ultimo = &(*novo)->esq;
  while( (*ultimo)->dir != NULL ){
    ultimo = &(*ultimo)->dir;
  }

  printf("No = %d\n", (*ultimo)->dado);

  (*novo)->dado = (*ultimo)->dado;
  free(*ultimo);
  (*ultimo) = NULL;

  return 1;
}



void preOrdem(arv arvore){
  if( vazia(arvore) )
    return;

  printf("%d ", arvore->dado);

  if( arvore->esq != NULL )
    preOrdem(arvore->esq);

  if( arvore->dir != NULL )
    preOrdem(arvore->dir);
}

void inOrdem(arv arvore){
  if( vazia(arvore) )
    return;

  if( arvore->esq != NULL )
    inOrdem(arvore->esq);

  printf("%d ", arvore->dado);

  if( arvore->dir != NULL )
    inOrdem(arvore->dir);
}

void posOrdem(arv arvore){
  if( vazia(arvore) )
    return;

  if( arvore->esq != NULL )
    posOrdem(arvore->esq);

  if( arvore->dir != NULL )
    posOrdem(arvore->dir);

  printf("%d ", arvore->dado);
}




/**
 * Duplica um caracter s por max vezes.
 */
void replica(char s, int max){
    while( max > 0 ){
      printf("%c", s);
      max--;
    }
}

/**
 * Exibição da árvore em pré-ordem.
 */
void exibir(arv arvore, int desloc){
  if( vazia(arvore) )
    return;

  printf("%d", arvore->dado);
  printf("\n");

  if( arvore->esq != NULL ){
    replica(' ', desloc);
    printf("esq: ");
    exibir(arvore->esq, desloc + 2);
  }
  if( arvore->dir != NULL ){
    replica(' ', desloc);
    printf("dir: ");
    exibir(arvore->dir, desloc + 2);
  }
}
