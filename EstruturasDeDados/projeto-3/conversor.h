/**
 * Avoid conflict with pilha.h when compiling.
 */
#ifndef MOSTRAR

	/* Define que a execu��o da transforma��o infixa em p�s-
	fixa ser� apresentada na tela */
	#define MOSTRAR 1

	/* Define que a execu��o da transforma��o da
	express�o infixa em p�s-fixa n�o ser� apresentada na tela */
	#define NAO_MOSTRAR 0

	/* tipo base dos elementos da �rvore */
	typedef char telem;

	/* n� da �rvore */
	typedef struct no {
		struct no *esq;
		telem info;
		struct no *dir;
	} tno;

	/* ponteiro para a raiz da �rvore */
	typedef tno *tab;

	/**
	 * Fun��es do projeto.
	 */
	int expressaoInfixaValida(char *expressao);
	char* obterOperandos(char *expressao);
	char* obterExpressaoPosfixa(tab *T);
	tab* converteInfixaParaArvore(char *expressao, int mostrarExecucao); // Falta imprimir
	float executaExpressao(tab *T, char *operandos, float *valor);

#endif
