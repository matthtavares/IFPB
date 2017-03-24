#include <stdio.h>
#include "arvore.h"

int main(){
  arv arvore, novo;
  inicializa(&arvore);

  inserir(&arvore, 20);
  inserir(&arvore, 21);
  inserir(&arvore, 10);
  inserir(&arvore, 11);
  inserir(&arvore, 6);

  exibir(arvore, 0);

  printf("\n\n");

  inserir(&arvore, 4);
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

  inserir(&arvore, 7);
  inserir(&arvore, 8);
  exibir(arvore, 0);
  printf("\n\n");

  /*printf("Removendo 4...\n");
  if( remover(&arvore, 4) ){
    exibir(arvore, 0);
    printf("\n\n");
  }
  printf("\n\n");

  printf("Removendo 11...\n");
  if( remover(&arvore, 11) ){
    exibir(arvore, 0);
    printf("\n\n");
  }*/
  printf("\n\n");

  /*printf("Removendo 7...\n");
  if( remover(&arvore, 7) ){
    exibir(arvore, 0);
    printf("\n\n");
  }
  printf("\n\n");*/

  printf("Removendo 10...\n");
  if( remover(&arvore, 10) ){
    exibir(arvore, 0);
    printf("\n\n");
  }

  return 0;
}
