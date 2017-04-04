#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversor.h"

int main(){
    //system("clear");

    int valida;
    char infixa, *operandos, *posfixa;
    tab *arv;
    float valores[3] = {5,10,6}, total;

    // while(1){
        printf("\n\n");

        printf("Digite a expressao: ");
        scanf("%s", &infixa);

        valida = expressaoInfixaValida(&infixa);
        printf("Eh valida = %d\n", valida);

        arv = converteInfixaParaArvore(&infixa, MOSTRAR);
        posfixa = obterExpressaoPosfixa(arv);
        printf("Pos-ordem: %s\n", posfixa);

        operandos = obterOperandos(&infixa);
        printf("Operandos: %s\n", operandos);

        total = executaExpressao(arv, operandos, valores);
        printf("Total = %.2f\n", total);

        printf("\n\n");
    // }

    return 0;
}
