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

/*
* Converte uma expressã
o infixa para posfixa.
* ARGUMENTOS:
*   char *expressao – A expressã
o no formato infixo digitada (string).
*   int mostrarExecucao –
Um inteiro que define se o passo-a-passo da
*                       transformação  da expressão infixa em pós-fixa será
*                       exibida na tela
* RETORNO:
*    Ponteiro para o nó raiz da arvore que representa a expressão
.
*    A árvore é
alocada dinamicamente.
*/
tab* converteInfixaParaArvore(char *expressao, int mostrarExecucao);

/*
* Verifica se a expressão infixa passada como argumento é válida ou nã
o.
* ARGUMENTOS:
*    char *expressao – A expressã
o (string) no formato infixo.
* RETORNO:
*    1 – quando a expressão é vá
lida.
*    0 – quando a expressão não é vá
lida
*/
int expressaoInfixaValida( char *expressao );
/*
* Identifica os operandos existentes na expressão infixa ou pós-fixa. A
string é
alocada dinamicamente.
* ARGUMENTOS:
*   char *expressao – A expressão no formato infixo ou pó
s-fixo.
* RETORNO:
*     Um apontador para char (string) contendo a lista de operandos
identificados   na   expressão,   sem   duplicidade.   A   cadeia   de   caracteres
(strings) é
alocada
*   dinamicamente.
*/
char* obterOperandos( char *expressao );

/*
* Identifica a expressão pos-fixa à partir da árvore binaria. A string é
alocada dinamicamente.
* ARGUMENTOS:
*   tab *T – A arvore binaria que corresponde à expressão
.
* RETORNO:
*   Um apontador para char (string) contendo a expressão no formato pos-
fixo. A cadeia de caracteres (strings) é
alocada dinamicamente.
*/
char* obterExpressaoPosfixa( tab *T );

/*
* Executa a expressã
o posfixada, de acordo com seus respectivos valores.
* ARGUMENTOS:
*   char *expressao – A expressão (string) no formato pó
s-fixo.
*   char *operandos – A sequê
ncia de operandos, sob a forma de um string,
*                     existente na expressão. Nã
o pode haver operandos
repetidos.
*   float *valor –
Um array de valores do tipo float com os respectivos
valores de
*                  cada operando existente em
char *operandos.
* RETORNO:
*   Um float com o resultado da expressã
o avaliada.
* EXEMPLO DE USO:
*   char *expressao = "ABCA*+-";
*   char *operandos = "ABC";  // Não conté
m duplicatas
*   char *valor = {2.0, 3.0, 4.0}; // A=2.0, B=3.0 e C=4.0
*/
float executaExpressao( tab *T, char *operandos, float *valor);


int prioridade(char e, char t);
void printPosfix(char *expressao);