#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversor.h"

int main(){

    int valida, mostrar = 0;
    char infixa, pp, *operandos, *posfixa;
    tab *arv;
    float valores[3] = {5}, total;

    while(1){
        system("clear");
        printf("# Conversor Infixa -> Posfixa\n\n");

        printf("Digite a expressao na forma infixa (quit: sair)\n> ");
        scanf("%s", &infixa);

        // If quit, break the loop
        // if( strcmp(infixa, "quit") == 0 )
            // break;

        printf("Deseja ver a transformacao passo-a-passo? (S/N)\n> ");
        scanf("%c", &pp);

        if( pp == 'S' )
            mostrar = 1;

        valida = expressaoInfixaValida(&infixa);
        printf("Eh valida = %d\n", valida);

        arv = converteInfixaParaArvore(&infixa, mostrar);
        posfixa = obterExpressaoPosfixa(arv);
        printf("Pos-ordem: %s\n", posfixa);

        operandos = obterOperandos(&infixa);
        printf("Operandos: %s\n", operandos);

        total = executaExpressao(arv, operandos, valores);
        printf("Total = %.2f\n", total);

        printf("\n\n");
    }

    system("clear");
    printf("# Conversor Infixa -> Posfixa\n\n");
    printf("Voce saiu do programa!\n");

    return 0;
}
