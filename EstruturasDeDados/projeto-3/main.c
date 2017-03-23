#include <stdio.h>
#include "arvore.h"

int main(){
  arv arvore;
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

  arv novo = busca(arvore, 10);
  printf("Busca valor = %d\n", novo->dado);

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

  printf("\n\n");

  printf("Esvaziando...");
  esvaziar(&arvore);

  printf("\n\n");

  exibir(arvore, 0);

  return 0;
}
