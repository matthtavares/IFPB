#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fila.h"

int main(){
    int operacao = 99;

    do {
        printf("Digite o codigo da operacao: ");
        scanf("%d", &operacao);

        printf("Opcao selecionada: %d\n", operacao);
    } while( operacao != 0 );

    system("cls");
    printf("Voce saiu do programa!\n");
    printf("\n\n");

    return 0;
}
