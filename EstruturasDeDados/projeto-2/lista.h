/**
 * Projeto de Estrutura de Dados
 * - Lista de Impress�o Ordenada
 *
 * Implementa��o de lista de impress�o com ordem de
 * prioridade utilizando lista encadeada com n� cabe�a.
 *
 * @author  Mateus Tavares
 * @author  Ronily Gomes
 */
typedef struct {
    char usuario[25];
    char documento[25];
    int paginas;
    int prioridade;
} impressao;

typedef struct stnolista {
	struct stnolista *ant;
	impressao dados;
    struct stnolista *prox;
} no;

typedef struct {
    no* inicio;
    no* fim;
    int tam;
} lista;

void inicializa(lista *lst);
int tamanho(lista lst);
int vazia(lista lst);
int inserir(lista *lst, impressao dados);
int remover(lista *lst, impressao *dados);
void listar(lista lst);
int limpar(lista *lst);
void povoar(lista *lst);
int atualizar(lista *lst, int code, int prioridade);
void PrintNext(lista *lst);