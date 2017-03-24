#include <stdio.h>
#include "arvore.h"

int main(){
  arv arvore, novo;
  inicializa(&arvore);

  inserir(&arvore, 10);
  inserir(&arvore, 8);
  inserir(&arvore, 11);

  exibir(arvore, 0);

  printf("\n\n");

  inserir(&arvore, 5);
  inserir(&arvore, 9);
  exibir(arvore, 0);

  printf("\n\n");

  /*int valor = 11;
  novo = busca(arvore, valor);
  if( novo != NULL )
    printf("Busca valor = %d\n", novo->dado);
  else
    printf("Não existe o valor %d na arvore!", valor);

  printf("\n\n");

  printf("Pre-ordem: ");
  preOrdem(arvore);

  printf("\n\n");

  printf("In-ordem: ");
  inOrdem(arvore);

  printf("\n\n");

  printf("Pos-ordem: ");
  posOrdem(arvore);

  printf("\n\n");

  exibir(arvore, 0);

  printf("\n\n");*/

  // printf("Esvaziando...");
  // esvaziar(&arvore);

  // printf("\n\n");

  // exibir(arvore, 0);

  novo = busca(arvore, 9);
  if( remover(&arvore, 10) ){
    exibir(arvore, 0);
    printf("\n\n");
  }

  return 0;
}
