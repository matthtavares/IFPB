#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"

int main(){
    lista listaimpressao;
    impressao novo;
    char *buffer;
    int i;

    inicializa(&listaimpressao);

    printf("Tamanho = %d\n", tamanho(listaimpressao));
    printf("Fila Vazia = %d\n", vazia(listaimpressao));

    printf("\n\n");

    // for(i = 0; i < 20; i++){
    //     sprintf(buffer, "Folha de Ponto %d", i+1);
    //     strcpy(novo.documento, buffer);
    //     strcpy(novo.usuario, "Mateus");
    //     novo.paginas = 2 * (i + 1);
    //     novo.prioridade = 1; //(i % 3) + 1;

    //     inserir(&listaimpressao, novo);
    // }

    // for(i = 20; i < 25; i++){
    //     sprintf(novo.documento, "Folha de Ponto %d", i+1);
    //     strcpy(novo.usuario, "Mateus");
    //     novo.paginas = 2 * (i + 1);
    //     novo.prioridade = 1; //(i % 3) + 1;

    //     inserir(&listaimpressao, novo);
    // }

    // for(i = 25; i < 30; i++){
    //     sprintf(novo.documento, "Folha de Ponto %d", i+1);
    //     strcpy(novo.usuario, "Mateus");
    //     novo.paginas = 2 * (i + 1);
    //     novo.prioridade = 2; //(i % 3) + 1;

    //     inserir(&listaimpressao, novo);
    // }

    // printf("\n\n");

    // printf("Tamanho = %d\n", tamanho(listaimpressao));
    // printf("Fila Vazia = %d\n", filaVazia(listaimpressao));

    // printf("\n\n");

    // listar(listaimpressao);

    // printf("## Inicio:\n");
    // imprimeInicio(listaimpressao);

    // printf("## Fim:\n");
    // imprimeFim(listaimpressao);

    // //listarReverso(listaimpressao);

    // printf("\n\n");

    // printf("## Esvaziar buffer:\n");
    // limpar(&listaimpressao);

    // printf("\n\n");

    // printf("Tamanho = %d\n", tamanho(listaimpressao));
    // printf("Fila Vazia = %d\n", filaVazia(listaimpressao));

    //povoar(&listaimpressao);
    listar(listaimpressao);

    printf("\n\n");

    // printf("## Removendo elemento...\n");
    // remover(&listaimpressao, &novo);
    // printf("## Dados do elemento removido:\n");
    // printf("Prioridade: %d\n", novo.prioridade);
    // printf("Usuario: %s\n", novo.usuario);
    // printf("Documento: %s\n", novo.documento);
    // printf("Paginas: %d\n\n", novo.paginas);

    // listar(listaimpressao);

    // printf("## Inicio:\n");
    // imprimeInicio(listaimpressao);

    // printf("## Fim:\n");
    // imprimeFim(listaimpressao);

    return 0;
}
