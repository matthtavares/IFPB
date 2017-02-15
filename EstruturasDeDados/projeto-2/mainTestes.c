#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"

int main(){
    lista listaimpressao;
    impressao novo;
    char buffer[50];
    int i;

    printf("# Iniciando:\n");
    inicializa(&listaimpressao);
    printf("Tamanho = %d\n", tamanho(listaimpressao));
    printf("Fila Vazia = %d\n", vazia(listaimpressao));
    printf("\n\n");

    for(i = 0; i < 5; i++){
        sprintf(buffer, "Folha de Ponto %d", i+1);
        strcpy(novo.documento, buffer);
        strcpy(novo.usuario, "Mateus");
        novo.paginas = 2 * (i + 1);
        novo.prioridade = (i % 3) + 1;

        inserir(&listaimpressao, novo);
    }

    printf("# Listando primeira insercao:\n");
    listar(listaimpressao);
    printf("Tamanho = %d\n", tamanho(listaimpressao));
    printf("Fila Vazia = %d\n", vazia(listaimpressao));
    printf("\n\n");

    printf("## Inicio:\n");
    imprimeInicio(listaimpressao);

    printf("## Fim:\n");
    imprimeFim(listaimpressao);

    printf("# Listando reversamente:\n");
    listarReverso(listaimpressao);
    printf("\n\n");

    printf("# Removendo elemento...\n");
    remover(&listaimpressao, &novo);
    printf("## Dados do elemento removido:\n");
    printf("Prioridade: %d\n", novo.prioridade);
    printf("Usuario: %s\n", novo.usuario);
    printf("Documento: %s\n", novo.documento);
    printf("Paginas: %d\n\n", novo.paginas);
    printf("\n\n");

    printf("# Listando apos remocao:\n");
    listar(listaimpressao);
    printf("\n\n");

    printf("## Inicio:\n");
    imprimeInicio(listaimpressao);

    printf("## Fim:\n");
    imprimeFim(listaimpressao);
    printf("\n\n");

    printf("# Povoando automaticamente...\n");
    povoar(&listaimpressao);

    printf("# Listando apos povoacao:\n");
    listar(listaimpressao);
    printf("\n\n");

    return 0;
}
