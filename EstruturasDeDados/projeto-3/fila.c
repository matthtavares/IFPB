/**
 * Projeto de Estrutura de Dados
 * - Lista de Impressão Ordenada
 *
 * Implementação de lista de impressão com ordem de
 * prioridade utilizando lista encadeada com nó cabeça.
 *
 * @author  Mateus Tavares
 * @author  Ronily Gomes
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "fila.h"

/**
 * Inicializa a lista.
 */
void inicializa(lista *lst){
    lst->tam = 0;
    lst->inicio = lst->fim = NULL;
}

/**
 * Retorna o tamanho da lista.
 *
 * @return  int
 */
int tamanho(lista lst){
    return lst.tam;
}

/**
 * Informa se a lista está vazia.
 *
 * @return  int  1 = TRUE, 0 = FALSE
 */
int vazia(lista lst){
    return (lst.tam == 0);
}

/**
 * Inserir um elemento na lista.
 *
 * @param   lista  lista a ser modificada.
 * @param   no    Dados a serem inseridos na lista.
 * @return  int   1 = SUCCESS, 0 = ERROR
 */
int inserir(lista *lst, impressao dados){
    no *novo;
    no *aux;
    no *ant;

    /// Tenta alocar memória para o novo elemento.
    if( (novo = (no*)malloc(sizeof(no))) == NULL )
        return 0;

    novo->dados = dados;
	novo->ant = NULL;
	novo->prox = NULL;

    /// Inserir na lista vazia
    if( vazia(*lst) ){
        lst->inicio = lst->fim = novo;
    } else {
        /// Inserir na lista com elementos
        ant = NULL;
        aux = lst->inicio;

        if( dados.prioridade == 1 ){
        	lst->fim->prox = novo;
        	novo->ant = lst->fim;
        	lst->fim = novo;
        } else if( dados.prioridade == aux->dados.prioridade ) {
        	// while( aux != NULL && (dados.prioridade < aux->dados.prioridade || dados.prioridade == aux->dados.prioridade) ){
        	while( aux != NULL && (dados.prioridade == aux->dados.prioridade) ){
        		ant = aux;
        		aux = aux->prox;
        	}
        	novo->ant = ant;
        	novo->prox = ant->prox;
        	ant->prox = novo;
	    }
    }

	/// Incrementa tamanho da lista.
    (lst->tam)++;

    return 1;
}

/**
 * Remove um elemento da lista.
 *
 * @param   lista  lista a ser processada.
 * @param   no    Endereço do elemento para retorno dos dados.
 * @return  int   1 = SUCCESS, 0 = FALSE
 */
int remover(lista *lst, impressao *dados){
	if( vazia(*lst) )
		return 0;

	no *aux = lst->inicio;
	*dados = aux->dados;
	lst->inicio = aux->prox;

	(lst->tam)--;

	free(aux);

	return 1;
}

/**
 * Lista todos os elementos da lista.
 *
 * @param   lista  lista a ser processada.
 */
void listar(lista lst){
    no *aux = lst.inicio;
    if( !vazia(lst) ){
        while( aux != NULL ){
            printf("Prioridade: %d\n", aux->dados.prioridade);
            printf("Usuario: %s\n", aux->dados.usuario);
            printf("Documento: %s\n", aux->dados.documento);
            printf("Paginas: %d\n\n", aux->dados.paginas);
            aux = aux->prox;
        }
    }
}

/**
 * Esvazia o buffer de impressão.
 *
 * @param   lista  lista a ser processada.
 * @return  int   1 = SUCCESS, 0 = ERROR
 */
int limpar(lista *lst){
	if( vazia(*lst) )
		return 0;

	no *aux;
	impressao dados;

	while( aux != NULL ){
		aux = lst->inicio->prox;
		remover(lst, &dados);
		lst->inicio = aux;
	}

	lst->inicio = NULL;
	lst->fim = NULL;
	lst->tam = 0;

	return 1;
}

/**
 * Insere automaticamente 10 elementos.
 *
 * @param   lista  lista a ser processada.
 * @return  int   1 = SUCCESS, 0 = ERROR
 */
int povoar(lista *lst){
    int i;
	impressao novo;
    for(i = 0; i < 10; i++){
        sprintf(novo.documento, "Folha de Ponto %d", i+1);
        sprintf(novo.usuario, "Usuario %d", (i % 3) + 1);
        novo.paginas = 2 * (i + 1);
        novo.prioridade = (i % 3) + 1;

        inserir(lst, novo);
    }
    return 1;
}

/**
 * Validar valor de prioridade.
 * Permite apenas de 1 a 3.
 *
 * @param  int  Valor da Prioridade
 * @return int  1 = VALID, 0 = INVALID
 */
int validarPrioridade(int priori){
    return ( priori >= 1 && priori <= 3);
}


void imprimeInicio(lista lst){
	no *aux = lst.inicio;
	printf("Prioridade: %d\n", aux->dados.prioridade);
    printf("Usuario: %s\n", aux->dados.usuario);
    printf("Documento: %s\n", aux->dados.documento);
    printf("Paginas: %d\n\n", aux->dados.paginas);
}
void imprimeFim(lista lst){
	no *aux = lst.fim;
	printf("Prioridade: %d\n", aux->dados.prioridade);
    printf("Usuario: %s\n", aux->dados.usuario);
    printf("Documento: %s\n", aux->dados.documento);
    printf("Paginas: %d\n\n", aux->dados.paginas);
}