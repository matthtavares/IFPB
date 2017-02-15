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

### Inserir

Utilizada para inserir elementos na lista.

**Parâmetros:**
* *lista *lst*: Recebe a lista por referência.
* *impressao dados*: Estrutura com os dados do elemento.

**Retorno:**
* Retorna um inteiro com **1** para *sucesso* e **0** para *erro*.

```
int inserir(lista *lst, impressao dados);
```

### Remover

Utilizada para remover elemento na lista. O elemento a ser removido será o do inicio da lista.

**Parâmetros:**
* *lista *lst*: Recebe a lista por referência.
* *impressao *dados*: Recebe a estrutura com os dados do elemento por referência.

**Retorno:**
* Retorna um inteiro com **1** para *sucesso* e **0** para *erro*.

```
int remover(lista *lst, impressao *dados);
```

### Listar

Irá lista os elementos da lista.

**Parâmetros:**
* *lista lst*: Recebe a lista por valor.

```
void listar(lista lst);
```

### Limpar

Utilizada para limpar toda a lista.

**Parâmetros:**
* *lista *lst*: Recebe a lista por referência.

**Retorno:**
* Retorna um inteiro com **1** para *sucesso* e **0** para *erro*.

```
int limpar(lista *lst);
```

### Povoar

Utilizada para inserir automaticamente 10 elementos na lista.

**Parâmetros:**
* *lista *lst*: Recebe a lista por referência.

```
void povoar(lista *lst);
```
