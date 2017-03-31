#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projeto.h"

int main(){
    printf("Hello World!\n");

    char infixa, *operandos, *posfixa;
    tab *arv;

    while(1){
        printf("Digite a expressao: ");
        scanf("%s", &infixa);

        arv = converteInfixaParaArvore(&infixa, MOSTRAR);
        posfixa = obterExpressaoPosfixa(arv);
        printf("Pos-ordem: %s\n", posfixa);

        operandos = obterOperandos(&infixa);
        printf("Operandos: %s", operandos);
        printf("\n\n");
    }

    return 0;
}
