# DOCUMENTAÇÃO

Para a correta utilização dos códigos disponibilizados, a leitura desta documentação é recomendada.

**Obs:** Este projeto foi desenvolvido para apresentação no sistema operacional Windows 7.

## Funções

### Inicializa

Para o correto funcionamento do programa, esta função deve ser utilizada para inicializar a lista.

**Parâmetros:**
* *lista *lst*: Recebe a lista por referência.

```
void inicializa(lista *lst);
```

### Tamanho

Retorna o tamanho (ou a quantidade de elementos) da lista.

**Parâmetros:**
* *lista lst*: Recebe a lista por valor.

**Retorno:**
* Retorna um inteiro com a quantidade de elementos presentes na lista.

```
int tamanho(lista lst);
```

### Vazia

Retorna se a lista está vazia ou não.

**Parâmetros:**
* *lista lst*: Recebe a lista por valor.

**Retorno:**
* Retorna um inteiro com **1** para *lista vazia* e **0**, para *lista com elementos*.

```
int vazia(lista lst);
```
