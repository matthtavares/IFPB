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

no busca(arv arvore, int dado){
  no achou;

  if( vazia(arvore) )
    return;

  if( arvore->dado == dado ){
    return *arvore;
  }

  if( arvore->esq != NULL )
    achou = busca(arvore->esq, dado);

  if( arvore->dir != NULL )
    achou = busca(arvore->dir, dado);

  return achou;
}

void replica(char s, int max){
    while( max > 0 ){
      printf("%c", s);
      max--;
    }
}

void exibir(arv arvore, int desloc){
  if( vazia(arvore) )
    return;

  printf("%d", arvore->dado);
  printf("\n");

  if( arvore->esq != NULL ){
    replica(' ', desloc);
    printf("|");
    replica('-', desloc);
    printf(" esq: ");
    exibir(arvore->esq, desloc + 2);
  }
  if( arvore->dir != NULL ){
    replica(' ', desloc);
    printf("|");
    replica('-', desloc);
    printf(" dir: ");
    exibir(arvore->dir, desloc + 2);
  }
}
