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

  no novo = busca(arvore, 10);
  printf("Busca valor = %d\n", novo.dado);

  return 0;
}
