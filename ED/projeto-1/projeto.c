#include "projeto.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//concluido
void criar(lista *lst){
	*lst = NULL;
}

//concluido
int vazia(lista lst){
	return lst == NULL;
}

//concluido
int tamanho(lista lst){

	lista aux = lst;
	int count = 0;

	while(aux != NULL){

		aux = aux->prox;
		count++;
	}

	return count;
}

//implemetar interface -> Mateus
/*
void menu()
{
	printf("----------- AGENDA -----------\n");
	printf("Menu: \n\n");
	printf("Inserir[1]\n");
	printf("Listar[2]\n");
	printf("Editar[3]\n");
	printf("Remover[4]\n");
	printf("Buscar[5]\n");
	printf("Posicao[6]\n\n");
}
*/

//concluido
int elemento(lista lst, int posicao, lista *retorno)
{
	lista aux = lst;
	int count = 1;

	if(vazia(lst) || posicao < 1 || posicao > tamanho(lst))
		return 0;

	while(aux != NULL && count < posicao){

		aux = aux->prox;
		count++;
	}

	if(aux != NULL){

		*retorno = aux;
		return 1;
	}

	return 0;
}

//concluido
int busca(lista lst, char *nome)
{
	if(!vazia(lst))
	{
		lista aux = lst;
		int count = 1;

		while(aux != NULL)
		{
			if(stricmp(aux->nome,nome) == 0)
				return count;
			aux = aux->prox;
			count++;
		}
	}
	return 0;
}

//concluido
int listar(lista lst, int posicao){
	lista aux = lst;
	int count = 1;

	if((vazia(lst)) || (posicao < 1) || (posicao > tamanho(lst)))
		return 0;

	while(aux != NULL && count < posicao){

		aux = aux->prox;
		count++;
	}

	if(aux != NULL){
		// implemetar interface -> Mateus
		printf("Nome: %s\n", aux->nome);
		printf("Email: %s\n", aux->email);
		printf("Tel: %d\n", aux->telefone);
		printf("data: %d/%d/%d\n", aux->dt_nascimento.dia,aux->dt_nascimento.mes,aux->dt_nascimento.ano);
		return 1;
	}
	return 0;
}

//concluido
int inserir(lista *lst, int posicao, no valor)
{
	lista aux;
	no *novo;
	int count;

	if( !validaNome(valor.nome) || !validaEmail(valor.email) || !validaData(valor.dt_nascimento))
		return 0;

	if( !verificaTelefone(*lst,valor.telefone) ){
		return 0;
	}

	if(vazia(*lst))
	{
		if(posicao != 1)
			return 0;

		if((novo = (no*) malloc(sizeof(no))) == NULL)
			return 0;

		*novo = valor;
		novo->prox = NULL;
		*lst = novo;
		return 1;
	}

	if(posicao == 1)
	{
		if((novo = (no*) malloc(sizeof(no))) == NULL)
			return 0;

		*novo = valor;
		novo->prox = *lst;
		*lst = novo;
		return 1;
	}

	aux = *lst;
	count = 1;
	while(count < posicao-1 && aux != NULL)
	{
		aux = aux->prox;
		count++;
	}

	if( aux == NULL)
		return 0;

	if((novo = (no*) malloc(sizeof(no))) == NULL)
		return 0;

	*novo = valor;
	novo->prox = aux->prox;
	aux->prox = novo;
	return 1;
}

//concluido
int atualizar( lista *lst, int posicao, no valor){

	lista aux = *lst;
	int count = 1;

	if(vazia(*lst) || posicao < 1 || posicao > tamanho(*lst))
		return 0;

	if( !validaNome(valor.nome) || !validaEmail(valor.email) || !validaData(valor.dt_nascimento) )
		return 0;

	if( !verificaTelefone(*lst,valor.telefone) ){
		return 0;
	}

	while(aux != NULL && count < posicao)
	{
		aux = aux->prox;
		count++;
	}

	if(aux == NULL)
		return 0;

	valor.prox = aux->prox;
	*aux = valor;

	return 1;
}

//concluido
int remover(lista *lst, int posicao, int *telefone){

	lista aux;
	no *prev;
	int count;

	if(vazia(*lst) || posicao < 1 || posicao > tamanho(*lst))
		return 0;

	aux = *lst;
	count = 1;

	while(count <= posicao-1 && aux != NULL){

		prev = aux;
		aux = aux->prox;
		count++;
	}


	if(aux == NULL)
		return 0;

	*telefone = aux->telefone;

	if(posicao == 1)
		*lst = aux->prox;
	else
		prev->prox = aux->prox;

	free(aux);
	return 1;
}

//concluido
int limpar(lista *lst){

	while(*lst != NULL){
		free(*lst);
		(*lst) = (*lst)->prox;
	}
	free(*lst);
}

// implemetar interface -> Mateus
void imprime (lista lst){

	lista aux = lst;

	while(aux != NULL){

		printf("Nome: %s\n", aux->nome);
		printf("Email: %s\n", aux->email);
		printf("Tel: %d\n", aux->telefone);
		printf("data: %d/%d/%d\n\n", aux->dt_nascimento.dia,aux->dt_nascimento.mes,aux->dt_nascimento.ano);
		aux = aux->prox;
	}
}

//concluido
int validaNome(char nome[]){

	int i;
	for(i = 0; nome[i] != '\0'; i++){
		if(nome[i] >= 'A' && nome[i] <= 'z') return 1;
	}
	return 0;
}

//concluido
int validaEmail(char email[]){
		int i;
	for(i = 0; email[i] != '\0'; i++){
		if(email[i] == '@') return 1;
	}
	return 0;
}

// perguntar na aula
/*
	int validaTelefone(int telefone){

	}
*/

//concluido
int validaData(data d){
	if(d.ano > 2016) return 0;
	if(d.ano < 1850) return 0;
	return 1;
}

//concluido
int verificaTelefone(lista lst, int tel){
	lista aux = lst;

	while(aux != NULL){

		if(aux->telefone == tel)
			return 0;
		aux = aux->prox;
	}
	return 1;
}
