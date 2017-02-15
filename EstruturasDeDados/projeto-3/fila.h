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
typedef struct {
    char* usuario;
    char* documento;
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
int povoar(lista *lst);

void imprimeInicio(lista lst);
void imprimeFim(lista lst);