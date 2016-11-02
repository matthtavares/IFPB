/**
 * Programa criado como primeiro projeto para
 * a disciplina de Estrutura de Dados do IFPB.
 *
 * https://github.com/matthtavares/IFPB/tree/master/ED/projeto-1
 *
 * @author  Ronily Gomes  <ronilyweb@gmail.com>
 * @author  Mateus Tavares  <mateus460@gmail.com>
 */

#include "agenda.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * Cria um novo registro da lista.
 *
 * @param   (lista)  Lista que será verificada
 */
void criar(lista *lst){
	*lst = NULL;
}

/**
 * Verifica se a lista está vazia.
 *
 * @param   (lista)  Lista que será verificada
 * @return  (int)    0 = Com registros / 1 = Vazia
 */
int vazia(lista lst){
	return lst == NULL;
}

/**
 * Verifica a quantidade de registros na lista.
 *
 * @param   (lista)  Lista que será pesquisada
 * @return  (int)    Quantidade de registros
 */
int tamanho(lista lst){

	lista aux = lst;
	int count = 0;

	while(aux != NULL){

		aux = aux->prox;
		count++;
	}

	return count;
}

/**
 * Imprime menu do programa.
 */
void menu()
{
	printf("\t\t----------- AGENDA -----------\n\n");
	printf("# MENU: \n\n");
	printf("[1] Inserir   Contado\n");
	printf("[2] Editar    Contato\n");
	printf("[3] Excluir   Contato\n");
	printf("[4] Verificar Contato\n");
	printf("[5] Listar    Registros\n");
	printf("[6] Excluir   Registros\n");
	printf("[7] Sair\n\n");
}

/**
 * Retorna dados de um registro pela posição requisitada.
 *
 * @param   (lista)  Lista que será verificada
 * @param   (int)    Posição do registro
 * @param   (lista)  Local onde será armazenado os dados do registro, caso exista.
 * @return  (int)    0 = Erro / 1 = Sucesso
 */
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

/**
 * Pesquisa por um registro com base no nome
 * do contato.
 *
 * @param   (lista)  Lista que será verificada
 * @param   (char)   Nome do contato
 * @return  (int)    0 = Erro / count = Quantidade de registros encontrados
 */
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

/**
 * Lista dados de um contato com base na sua posição.
 *
 * @param   (lista)  Lista que será verificada
 * @param   (int)    Posição do contato
 * @return  (int)    0 = Erro / 1 = Sucesso
 */
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
		return 1;
	}
	return 0;
}

/**
 * Insere um novo contato na lista.
 *
 * @param   (lista)  Lista onde será inserido o valor
 * @param   (int)    Posição do registro na lista
 * @param   (no)     Dados do contato
 * @return  (int)    0 = Erro / 1 = Sucesso
 */
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

/**
 * Atualizar dados de um contato.
 *
 * @param   (lista)  Lista que será verificada.
 * @param   (int)    Posição do registro na lista
 * @param   (no)     Dados do contato
 * @return  (int)    0 = Erro / 1 = Sucesso
 */
int atualizar( lista *lst, int posicao, no valor){

	lista aux = *lst;
	int count = 1;

	if(vazia(*lst) || posicao < 1 || posicao > tamanho(*lst))
		return 0;

	if( !validaNome(valor.nome) || !validaEmail(valor.email) || !validaData(valor.dt_nascimento) )
		return 0;

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

/**
 * Remove um registro da lista.
 *
 * @param   (lista)  Lista onde será inserido o valor
 * @param   (int)    Posição do registro na lista
 * @param   (int)    Endereço da variável que armazena o telefone do contato
 * @return  (int)    0 = Erro / 1 = Sucesso
 */
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

/**
 * Limpa a memória, removendo os elementos da lista.
 *
 * @param   (lista)  Lista onde será inserido o valor
 * @param   (int)    Posição do registro na lista
 * @param   (no)     Dados do contato
 * @return  (int)    0 = Erro / 1 = Sucesso
 */
int limpar(lista *lst){

	lista aux;
	while(*lst != NULL){
		aux = *lst;
		(*lst) = (*lst)->prox;
		free(aux);
	}

	return 1;
}

/**
 * Lista todos os registros da lista.
 *
 * @param   (lista)  Lista que será verificada
 */
void imprime (lista lst){

	lista aux = lst;

	while(aux != NULL){
		printf("Nome: %s\n", aux->nome);
		printf("Email: %s\n", aux->email);
		printf("Telefone: %d\n", aux->telefone);
		printf("Data de Nascimento: %d/%d/%d\n\n", aux->dt_nascimento.dia, aux->dt_nascimento.mes, aux->dt_nascimento.ano);
		aux = aux->prox;
	}
}

/**
 * Valida o nome do contato.
 *
 * @param   (char[])  String do nome do contato
 * @return  (int)     0 = Erro / 1 = Sucesso
 */
int validaNome(char nome[]){
	int i;
	int letras = 0;
	for(i = 0; nome[i] != '\0'; i++){
		if(isalpha(nome[i])) 
			letras++;
	}

	if(letras)
		return 1;
	else
		return 0;
}

/**
 * Valida o email do contato.
 *
 * @param   (char[])  String do email do contato
 * @return  (int)     0 = Erro / 1 = Sucesso
 */
int validaEmail(char email[]){
	int i;
	for(i = 0; email[i] != '\0'; i++){
		if(email[i] == '@') return 1;
	}
	return 0;
}

/**
 * Valida a data que foi inserida.
 *
 * @param   (data)  Data para verificar
 * @return  (int)   0 = Erro / 1 = Erro
 */
int validaData(data d){
	if(d.ano > 2016) return 0;
	if(d.ano < 1500) return 0;
	return 1;
}

/**
 * Verifica se o telefone já existe na lista.
 *
 * @param   (lista)  Lista a ser verificada
 * @param   (int)    Telefone que vai ser procurado
 * @return  (int)    0 = Erro / 1 = Sucesso
 */
int verificaTelefone(lista lst, int tel){
	lista aux = lst;

	while(aux != NULL){

		if(aux->telefone == tel)
			return 0;
		aux = aux->prox;
	}
	return 1;
}