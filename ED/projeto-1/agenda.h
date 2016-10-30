//definindo a estrutura de data
typedef struct{
    int dia;
    int mes;
    int ano;
}data;

// Definindo a estrutura de dados
typedef struct stnolista {
    char nome[20];
    int telefone;
    char email[20];
    data dt_nascimento;
    struct stnolista *prox; // campo do ponteiro para o proximo no
}no;

// Criando o tipo lista
typedef no* lista;

// Criando uma lista vazia
void criar(lista *lst);

// Verificar se a lista esta vazia
int vazia(lista lst);

// Obter o tamanho da lista
int tamanho(lista lst);

// Obter o valor do elemento de uma determinada posicao
int elemento (lista lst, int posicao, lista *retorno);

// Obter a posicao do elemento, cujo valor(nome) eh fornecido
int busca(lista lst, char *nome);

// Listar dados de uma determinada posicao
int listar(lista lst, int posicao);

// inserir um elemento na lista, dada a sua posicao
int inserir( lista *lst, int posicao, no valor);

// atualizar um elemento na lista, dada a sua posicao
int atualizar( lista *lst, int posicao, no valor);

// Remover um elemento de uma determinada posicao
int remover(lista *lst, int posicao, int *telefone);

// Remover todos os elementos da lista
int limpar(lista *lst);

// Exibe todos os elementos da lista
void imprime (lista lst);