#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projeto.h"

int main(){
    printf("Hello World!\n");

    /*telem valor;

    pilha p;
    criarPilha(&p);

    tab arv;
    tab arv2;
    criarArvore(&arv);
    criarArvore(&arv2);

    inserir(&arv, 'a');
    inserir(&arv2, 'b');

    empilhar(&p, &arv);
    empilhar(&p, &arv2);
    imprimePilha(p);

    printf("Desempilha...\n");
    //desempilhar(&p, &valor);
    //esvaziarPilha(&p);
    imprimePilha(p);*/

    char infixa;

    while(1){
        printf("Digite a expressao: ");
        gets(&infixa);

        converteInfixaParaArvore(&infixa, MOSTRAR);
    }



    return 0;
}

