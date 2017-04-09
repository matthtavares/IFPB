/**
 * Avoid conflict with pilha.h when compiling.
 */
#ifndef MOSTRAR

	/* Define que a execução da transformação infixa em pós-
	fixa será apresentada na tela */
	#define MOSTRAR 1

	/* Define que a execução da transformação da
	expressão infixa em pós-fixa não será apresentada na tela */
	#define NAO_MOSTRAR 0

	/* tipo base dos elementos da árvore */
	typedef char telem;

	/* nó da árvore */
	typedef struct no {
		struct no *esq;
		telem info;
		struct no *dir;
	} tno;

	/* ponteiro para a raiz da árvore */
	typedef tno *tab;

	/**
	 * Funções do projeto.
	 */
	int expressaoInfixaValida(char *expressao);
	char* obterOperandos(char *expressao);
	char* obterExpressaoPosfixa(tab *T);
	tab* converteInfixaParaArvore(char *expressao, int mostrarExecucao); // Falta imprimir
	float executaExpressao(tab *T, char *operandos, float *valor);

#endif
