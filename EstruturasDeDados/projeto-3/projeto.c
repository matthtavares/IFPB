#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include "projeto.h"

typedef struct stnopilha{
    char dado;
    struct stnopilha* prox;
} nop;
typedef struct {
	nop *inicio;
	int tam;
} pilha;

/**
 * Retorna o endereço para uma nova pilha.
 */
pilha* criaPilha(){
    pilha *p;
    p = (pilha*)malloc(sizeof(pilha*));
    p->inicio = NULL;
    p->tam = 0;
    return p;
}

/**
 * Verifica se a pilha está vazia.
 *
 * @param   pilha   p
 *
 * @return  int  0 = FALSE, 1 = TRUE
 */
int pilhaVazia(pilha p){
	return (p.tam == 0);
}

/**
 * Verifica o tamanho da pilha.
 *
 * @param   pilha   p
 *
 * @return  int
 */ 
int pilhaTamanho(pilha p){
	return p.tam;
}

/**
 * Inserir dado na pilha.
 *
 * @param   pilha   *p
 * @param   char    valor
 *
 * @return  int     0 = ERROR, 1 = SUCCESS
 */
int empilhar(pilha *p, char valor){
	nop *novo;
	novo = (nop*)malloc(sizeof(nop*));

	if( novo == NULL )
		return 0;

	novo->dado = valor;
	novo->prox = p->inicio;
	p->inicio = novo;

	p->tam++;

	return 1;
}

/**
 * Remover dado da pilha.
 *
 * @param   pilha   *p
 * @param   char    *valor
 *
 * @return  int     0 = ERROR, 1 = SUCCESS
 */
int desempilha(pilha *p, char *valor){
	if( pilhaVazia(*p) )
		return 0;

	nop *aux;
	aux = p->inicio;
	*valor = aux->dado;
	p->inicio = aux->prox;

	p->tam--;

	if( p->tam == 0 )
		p->inicio = NULL;

	free(aux);
	return 1;
}

/**
 * Remove todos os itens da pilha.
 *
 * @param   pilha   *p
 *
 * @return  int     0 = ERROR, 1 = SUCCESS
 */
int esvaziarPilha(pilha *p){
	if( pilhaVazia(*p) )
		return 0;

	nop *aux;
	aux = p->inicio;

	while( aux != NULL ){
		p->inicio = aux->prox;
		free(aux);
		aux = p->inicio;
		p->tam--;
	}

	free(p);

	return 1;
}

/**
 * Busca um dado na pilha.
 *
 * @return  int     0 = ERROR, 1 = SUCCESS
 */
int buscaPilha(pilha p, char dado){
	nop *aux = p.inicio;
	while( aux != NULL ){
		if( dado == aux->dado ){
			return 1;
		}
		aux = aux->prox;
	}
	return 0;
}

/**
 * Retorna o elemento no topo da pilha.
 *
 * @param   pilha   *p
 *
 * @return  char
 */
char pilhaTopo(pilha p){
	if( pilhaVazia(p) )
		return 0;

	nop *aux = p.inicio;
	return aux->dado;
}

/**
 * Imprime pilha.
 *
 * @param   pilha   p
 */
void imprimePilha(pilha p){
	int i = 1;
	nop *aux = p.inicio;
	while( aux != NULL ){
		printf("Valor %d = %c\n", i, aux->dado);
		aux = aux->prox;
		i++;
	}
}


/**
 * Cria uma arvore.
 */
tab* criaArvore(){
	tab *arv;
	arv = (tab*)malloc(sizeof(tab*));
	return arv;
}

int insereArvore(tab *arvore, telem dado){

}


/**
 * A prioridade varia, conforme o símbolo se encontre na entrada ou no topo da pilha, de acordo com a seguinte tabela: 
 *
 * +-----------+---------+----------+
 * |  SIMBOLO  |  PILHA  | ENTRADA  |
 * +-----------+---------+----------+
 * |     ^     |    3    |     4    |
 * +-----------+---------+----------+
 * |    * /    |    2    |     2    |
 * +-----------+---------+----------+
 * |    + -    |    1    |     1    |
 * +-----------+---------+----------+
 * |     (     |    0    |     4    |
 * +-----------+---------+----------+
 *
 * Fonte: http://www.vision.ime.usp.br/~pmiranda/mac122_2s14/aulas/aula13/aula13.html
 */
int prioridade(char e, char t){
  int pe, pt;
 
  if(e == '^')
    pe = 4;
  else if(e == '*' || e == '/')
    pe = 2;
  else if(e == '+' || e == '-')
    pe = 1;
  else if(e == '(')
    pe = 4;
 
  if(t == '^')
    pt = 3;
  else if(t == '*' || t == '/')
    pt = 2;
  else if(t == '+' || t == '-')
    pt = 1;
  else if(t == '(')
    pt = 0;
 
  return (pe > pt);
}

void printPosfix(char *expressao){
	pilha *p;
	int i = 0;
	char c, t;

	p = criaPilha();

	while( *expressao != '\0' ) {
		c = *expressao;

		if( c >= 'A' && c <= 'Z' ){
			printf("%c", c);
		}
		else if( c == '(' ){
			empilhar(p, c);
		}
		else if( c == ')' || c == '\0' ){
			do {
				desempilha(p, &t);
				if( t != '(' )
					printf("%c", t);
			} while( t != '(' );
		}
		else if( c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ){
			while( 1 ){
				desempilha(p, &t);
				if( prioridade(c, t) ){
					empilhar(p, t);
					empilhar(p, c);
					break;
				} else {
					printf("%c", t);
				}
			}
		}

		expressao++;
	}

	// Esvaziando pilha
	// *bug* apresentando letra a mais se tamanho >= 1 ou > 0
	while( pilhaTamanho(*p) > 1 ){
		desempilha(p, &t);
		printf("%c", t);
	}

	printf("\n\n");
	esvaziarPilha(p);
}

int expressaoInfixaValida( char *expressao ){
	char *aux;
	aux = expressao;
	while( *aux != '\0' ){
		if( *aux < 'A' && *aux > 'Z' && *aux != '/' && *aux != '*' && *aux != '+' && *aux != '-' && *aux != '(' && *aux != ')' && *aux != '^' ){
			return 0;
		}
		aux++;
	}
	return 1;
}

tab* converteInfixaParaArvore(char *expressao, int mostrarExecucao){
	tab *arvore;
	pilha *p;
	char *aux;

	p = criaPilha();

	if( (arvore = criaArvore()) == NULL )
		return NULL;

	aux = expressao;
	while( *aux != '\0' ){
		empilhar(p, *aux);
		aux++;
	}

	imprimePilha(*p);

	while( desempilha(p, aux) ){
		// Insere na árvore
	}

	esvaziarPilha(p);
	return arvore;
}

/**
 * JA FUNCIONA PORRA!
 */
char* obterOperandos(char *expressao){
	pilha *p;
	p = criaPilha();

	char *ret = (char*)malloc(sizeof(char*) * strlen(expressao));
	int i = 0;

	char *aux;
	aux = expressao;
	while( *aux != '\0' ){
		if( *aux >= 'A' && *aux <= 'Z' ){
			if( !buscaPilha(*p, *aux) ){
				empilhar(p, *aux);
				ret[i] = *aux;
				i++;
			}
		}
		aux++;
	}
	ret[i] = '\0';

	esvaziarPilha(p);
	return ret;
}