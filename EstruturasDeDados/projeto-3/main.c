#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include "conversor.h"

int main(){

    int i, valida, mostrar = NAO_MOSTRAR;
    char infixa[100], pp, *operandos;
    tab *arv;
    float *valores, total;

    while(1){
        system("cls");
        printf("# Conversor Infixa -> Posfixa\n\n");

        printf("Digite a expressao na forma infixa (quit: sair)\n> ");
        scanf("%s%*c", infixa);

        /// If quit, break the loop
        if( strcmp(infixa, "quit") == 0 )
            return 1;

        /// Valida a express?o
        while( expressaoInfixaValida(infixa) == 0 ){
            printf("\a\nA expressao eh invalida!\n");
            printf("Digite a expressao na forma infixa (quit: sair)\n> ");
            scanf("%s%*c", infixa);

            /// If quit, break the loop
            if( strcmp(infixa, "quit") == 0 )
                return 1;
        }

        printf("\nDeseja ver a transformacao passo-a-passo? (S/N)\n> ");
        scanf("%c%*c", &pp);
        pp = toupper(pp);

        while( pp != 'S' && pp != 'N' ){
            printf("\a\nPor favor, apenas S ou N!\n");
            printf("Deseja ver a transformacao passo-a-passo? (S/N)\n> ");
            scanf("%c%*c", &pp);
            pp = toupper(pp);
        }

        if( pp == 'S' )
            mostrar = MOSTRAR;

        /// Transforma a express?o em ?rvore
        arv = converteInfixaParaArvore(infixa, mostrar);

        /// Obt?m os operandos da express?o
        operandos = obterOperandos(infixa);

        /// Obt?m valores de cada operando
        printf("\nDigite os valores dos operandos identificados:\n");
        valores = (float*)malloc(sizeof(float) * strlen(operandos));
        for(i = 0; i < strlen(operandos); i++){
            printf("%c = ", operandos[i]);
            scanf("%f%*c", &valores[i]);
        }

        /// Executa o c?lculo
        total = executaExpressao(arv, operandos, valores);

        /// Imprime o resultado
        printf("\nO resultado da expressao eh\n> %.2f\n", total);

        printf("\n\n");
        system("pause");
    }

    /*
    system("cls");
    printf("# Conversor Infixa -> Posfixa\n\n");
    printf("Voce saiu do programa!\n\n\n");
    */

    return 0;
}
