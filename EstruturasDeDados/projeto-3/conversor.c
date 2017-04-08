#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "conversor.h"
#include "pilha.h"

/**
 * Inicializa a árvore.
 *
 * @param  tab  *arv  Endereço para árvore
 */
void criarArvore(tab *arv){
    *arv = NULL;
}

/**
 * Verifica se a árvore está vazia.
 *
 * @param  tab  arv  Árvore a ser verificada
 *
 * @return  int  0 = FALSE, 1 = TRUE
 */
int arvoreVazia(tab arv){
    return (arv == NULL);
}

/**
 * Inserir um dado na árvore.
 *
 * @param  tab    *arv  Endereço da árvore a ser modificada
 * @param  telem  dado  Dado a ser inserido
 *
 * @return int  0 = ERROR, 1 = SUCCESS
 */
int inserir(tab *arv, telem dado){
	tno *novo;
	tno *p = *arv;

	if( arvoreVazia(*arv) ){
		if( (novo = (tno*)malloc(sizeof(tno))) == NULL )
			return 0;

		novo->info = dado;
		novo->esq = novo->dir = NULL;

		*arv = novo;

		return 1;
	} else if( dado < p->info ) {
		return inserir(&p->esq, dado);
	} else if( dado > p->info ) {
		return inserir(&p->dir, dado);
	}

	return 0;
}

/**
 * Procura um dado na árvore.
 *
 * @param  tab    *arv  Endereço da árvore a ser verificada
 * @param  telem  dado  Dado a ser pesquisado
 *
 * @return tab*  Endereço do nó encontrado / NULL se não encontrar
 */
tab* busca(tab *arv, telem dado){
	tab *value = NULL;

	if( arvoreVazia(*arv) )
		return NULL;

	if( dado == (*arv)->info ){
		return arv;
	}

	if( (*arv)->esq != NULL )
		value = busca(&(*arv)->esq, dado);
	else if( value == NULL && (*arv)->dir != NULL )
		value = busca(&(*arv)->dir, dado);

	return value;
}

/**
 * Remover dado da árvore.
 *
 * @param  tab    *arv  Endereço da árvore a ser modificada
 * @param  telem  dado  Dado a ser removido
 *
 * @return int  0 = ERROR, 1 = SUCCESS
 */
int remover(tab *arv, telem dado){
	tab p;

	if( arvoreVazia(*arv) )
		return 0;

	tab *novo;
	novo = busca(arv, dado);

	// Se não tiver filhos
	if( (*novo)->esq == NULL && (*novo)->dir == NULL ){
		free((*novo));
		*novo = NULL;
		return 1;
	}

	// Se não houver filhos à esquerda
	if( (*novo)->esq == NULL ){
		p = (*novo)->dir;
		free((*novo));
		*novo = p;
		return 1;
	}

	// Se não houver filhos à direita
	if( (*novo)->dir == NULL ){
		p = (*novo)->esq;
		free((*novo));
		*novo = p;
		return 1;
	}

	// Se houver filhos em ambos os nós
	tab *ultimo;
	ultimo = &(*novo)->esq;
	while( (*ultimo)->dir != NULL ){
		ultimo = &(*ultimo)->dir;
	}

	(*novo)->info = (*ultimo)->info;
	free(*ultimo);
	(*ultimo) = NULL;

	return 1;
}

/**
 * Esvazia toda a árvore.
 *
 * @param  tab  *arv  Endereço da árvore a ser modificada
 */
void esvaziar(tab *arv){
	if( arvoreVazia(*arv) )
		return;

	esvaziar(&(*arv)->esq);
	esvaziar(&(*arv)->dir);

	free(*arv);

	*arv = NULL;
}

/**
 * FUNÇÕES DO PROJETO!
 */

/**
 * Converte string para letras maisculas.
 * http://stackoverflow.com/a/26328095
 */
char* strupr(char *s){
	char* tmp = s;

	for (;*tmp;++tmp) {
		*tmp = toupper((unsigned char) *tmp);
	}

	return s;
}

/**
 * Verifica a prioridade de um operando.
 *
 * @param  char  e  Operando informado
 *
 * @return  float  Valor total do calculo
 */
int prioridade(char e){
	switch( e ){
		case '(':
			return 1;
		case '+':
		case '-':
			return 2;
		case '*':
		case '/':
			return 3;
		case '^':
			return 4;
	}
}

/**
 * Retorna o valor de um operando.
 *
 * @param  char   operando    Operando desejado.
 * @param  char   *operandos  Endereço do vetor com os operandos válidos.
 * @param  float  *valores    Endereço do vetor de valores.
 *
 * @return float
 */
float getOprValue(char operando, char *operandos, float *valores){
	int i = 0;
	for(i = 0; operandos[i] != '\0'; i++){
		if( operandos[i] == operando )
			return valores[i];
	}
}

/**
 * Verifica se a expressao informada eh valida.
 *
 * @param  char   *expressao  String contendo a expressao informada
 *
 * @return  int  1 = Valida, 0 = Invalida
 */
int expressaoInfixaValida(char *expressao){
	char *aux, ant, prox;
	pilha paren;
	tab arv;

	// Verifica tamanho
	if( strlen(expressao) < 3 )
		return 0;

	// Se não começa com +-*/
	if(*expressao == '+' || *expressao == '-' || *expressao == '*' || *expressao == '/' || *expressao == '^')
		return 0;

	// Converte para maisculas
	strupr(expressao);
	aux = expressao;

	criarPilha(&paren);

	while( *aux != '\0' ){
		// Se for caracter invalido
		if( (*aux < 'A' || *aux > 'Z') && *aux != '+' && *aux != '-' && *aux != '*' && *aux != '/' && *aux != '^' && *aux != '(' && *aux != ')' )
			return 0;

		// +-/*^
		if( *aux == '+' || *aux == '-' || *aux == '*' || *aux == '/' || *aux == '^' ){
			ant = *(aux - 1);
			prox = *(aux + 1);

			// Devem estar entre operandos
			if( (ant < 'A' || ant > 'Z') || (prox < 'A' || prox > 'Z') )
				return 0;
		}

		// Digito não pode ser seguido de digito
		if( *aux >= 'A' && *aux <= 'Z' ){
			prox = *(aux + 1);

			if( prox >= 'A' && prox <= 'Z' )
				return 0;
		}

		// Verificar parenteses
		if( *aux == '(' ){
			criarArvore(&arv);
			inserir(&arv, *aux);
			empilhar(&paren, &arv);
		}
		if( *aux == ')' ){
			// Se a pilha estiver vazia, tem algo errado
			if( pilhaVazia(paren) )
				return 0;

			do {
				desempilhar(&paren, &arv);
			} while( arv->info != '(' );
		}

		aux++;
	}

	// Se a pilha não estiver vazia, erro
	if( !pilhaVazia(paren) )
		return 0;

	return 1;
}

/**
 * Agrupa os operandos em uma string sem duplicidade.
 *
 * @param  char   *expressao  String contendo a expressao digitada pelo usuario
 *
 * @return char*  String com operandos alocados em memória
 */
char* obterOperandos(char *expressao){
	pilha p;
	tab arv;
	criarPilha(&p);

	char *ret = (char*)malloc(sizeof(char*) * strlen(expressao));
	int i = 0;

	char *aux;
	aux = expressao;
	while( *aux != '\0' ){
		if( *aux >= 'A' && *aux <= 'Z' ){
			if( !buscaPilha(p, *aux) ){
        		criarArvore(&arv);
        		inserir(&arv, *aux);

				empilhar(&p, &arv);
				ret[i++] = *aux;
			}
		}
		aux++;
	}
	ret[i] = '\0';

	esvaziarPilha(&p);
	return ret;
}

/**
 * Obtem uma string contendo a expressao na forma posfixa.
 *
 * @param  tab  *T  Arvore contendo a expressao
 *
 * @return  char*  Endereco da string alocada em memória
 */
char* obterExpressaoPosfixa(tab *T){
	if( arvoreVazia(*T) )
		return NULL;

	char *ret = (char*)malloc(sizeof(char*));
	char *cat = (char*)malloc(sizeof(char*));
	strcpy(ret, "");

	if( (*T)->esq != NULL ){
		sprintf(cat, "%s", obterExpressaoPosfixa(&(*T)->esq));
		strcat(ret, cat);
	}

	if( (*T)->dir != NULL ){
		sprintf(cat, "%s", obterExpressaoPosfixa(&(*T)->dir));
		strcat(ret, cat);
	}

	sprintf(cat, "%c", (*T)->info);
	strcat(ret, cat);

	free(cat);

	return ret;
}

/**
 * Converte a expressao infixa para posfixa.
 *
 * @param  char   *expressao         String com a expressao digitada pelo usuario
 * @param  int    mostrarExecucao    Caso 1, mostra o processamento da expressao
 *
 * @return  tab*  Endereco da arvore alocada em memória
 */
tab* converteInfixaParaArvore(char *expressao, int mostrarExecucao){
	pilha operadores, saida;
	tab desempilha, opr, novo, *arv;
	char c;
	int priori;

	// Cria as pilhas para operadores e a saida
	criarPilha(&operadores);
	criarPilha(&saida);

	// Processa a string
	while( *expressao != '\0' ){
		c = *expressao;
		if( c >= 'A' && c <= 'Z' ){
			criarArvore(&novo);
			inserir(&novo, c);
			empilhar(&saida, &novo);
		}else if( c == '(' ){
			criarArvore(&novo);
			inserir(&novo, c);
			empilhar(&operadores, &novo);
		}else if( c == ')' ){
			do{
				desempilhar(&operadores, &opr);
				if( opr->info != '(' ){
					desempilhar(&saida, &opr->dir);
					desempilhar(&saida, &opr->esq);
					empilhar(&saida, &opr);
				}
			}while( opr->info != '(' );
		}else if( c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ){
			topo(operadores, &desempilha);
			priori = prioridade(c);
			while( 1 ){
				if( !pilhaVazia(operadores) && prioridade(desempilha->info) >= priori ){
					desempilhar(&operadores, &desempilha);

					desempilhar(&saida, &desempilha->dir);
					desempilhar(&saida, &desempilha->esq);
					empilhar(&saida, &desempilha);

					topo(operadores, &desempilha);
				} else {
					criarArvore(&novo);
					inserir(&novo, c);
					empilhar(&operadores, &novo);
					break;
				}
			}
		}
		expressao++;
	}

	// Esvazia pilha de operadores para saida
	while( desempilhar(&operadores, &desempilha) ){
		desempilhar(&saida, &desempilha->dir);
		desempilhar(&saida, &desempilha->esq);
		empilhar(&saida, &desempilha);
	}

	// Aloca a arvore
	arv = (tab*)malloc(sizeof(tab*));

	// Desempilha a saida para a arvore
	desempilhar(&saida, arv);

	return arv;
}

/**
 * Calcula a expressao posfixa.
 *
 * @param  tab    *T          Arvore com as operacoes
 * @param  char   *operandos  String contendo os operandos (sem duplicidade)
 * @param  float  *valores    Array com os valores de cada operando
 *
 * @return  float  Valor total do calculo
 */
float executaExpressao(tab *T, char *operandos, float *valores){
	vpilha resultados;
	char *posfixa;
	float x, y, valor;

	// Cria a pilha que armazena valores.
	criarIPilha(&resultados);

	// Obtem a string posfixa da arvore
	posfixa = obterExpressaoPosfixa(T);

	// Percorre a string
	while( *posfixa != '\0' ){
		// Se for uma letra
		if( *posfixa >= 'A' && *posfixa <= 'Z' ){
			// Obtem o valor do operando
			valor = getOprValue(*posfixa, operandos, valores);
			// Empilha o valor
			empilharV(&resultados, valor);
		}
		// Se for um operador
		else if( *posfixa == '+' || *posfixa == '-' || *posfixa == '*' || *posfixa == '/' || *posfixa == '^' ){
			// Desempilha os valores
			desempilharV(&resultados, &y);
			desempilharV(&resultados, &x);
			// Calcula e empilha o resultado
			switch(*posfixa){
				case '+': {
					empilharV(&resultados, (x+y));
					break;
				}
				case '-': {
					empilharV(&resultados, (x-y));
					break;
				}
				case '*': {
					empilharV(&resultados, (x*y));
					break;
				}
				case '/': {
					empilharV(&resultados, (x/y));
					break;
				}
				case '^': {
					empilharV(&resultados, pow(x,y));
					break;
				}
			}
		}
		posfixa++;
	}

	// Desempilha o total
	desempilharV(&resultados, &valor);

	// Retorna o valor total
	return valor;
}
