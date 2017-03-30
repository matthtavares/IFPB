#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projeto.h"

int main(){
    printf("Hello World!\n");

    char infixa;
    tab *arv;

    while(1){
        printf("Digite a expressao: ");
        scanf("%s", &infixa);

        arv = converteInfixaParaArvore(&infixa, MOSTRAR);
        posOrdem(*arv);
        printf("\n\n");
    }

    return 0;
}
