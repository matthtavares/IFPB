# Documentação das Funções

Estas descrições das referidas funções foram adaptadas de [*The Open Group Base Specifications Issue 7 (IEEE Std 1003.1-2008, 2016 Edition)*](http://pubs.opengroup.org/onlinepubs/9699919799/).

### open()

```
int open(const char *path, int oflag);
```

Ao dar um caminho para um arquivo, a função **open()** retorna um *descritor de arquivo*, um pequeno inteiro não-negativo, para ser utilizado em *system calls* posteriores [read(), write()]. Caso haja erro, -1 é retornado.

### read()

```
ssize_t read(int fildes, void *buf, size_t nbyte);
```

A função **read()** deve tentar ler *nbyte* bytes do arquivo associado ao descritor de arquivo aberto, *fildes*, para o buffer apontado por *buf*.

Se *read()* é interrompida por um sinal antes que leia todos os dados, ela deve retornar -1 com errno definido.
Se *read()* é interrompida por um sinal após ter lido com sucesso alguns dados, ele deve retornar o número de bytes lidos.

Para arquivos regulares, nenhuma transferência de dados deve ocorrer após o deslocamento máximo estabelecido na descrição de arquivo aberto associado a fildes. 

### write()

```
ssize_t write(int fildes , const void * buf , size_t nbyte );
```

A função **write()** deve tentar escrever *nbyte* bytes do buffer apontado por *buf* para o arquivo associado com o descritor de arquivo aberto, *fildes*.

Antes de qualquer ação ser realizada, verifica se *nbyte* é zero e o arquivo é um arquivo regular, a função *write()* pode detectar e retornar erros como descrito abaixo. Na ausência de erros, ou se a detecção de erros não é executada, a função *write()* deve retornar zero e não têm outros resultados. Se *nbyte* é zero e o arquivo não é um arquivo regular, os resultados não são especificados.

Em um arquivo regular ou outro arquivo capaz de busca, a própria escrita de dados deve proceder a partir da posição no arquivo indicado pelo deslocamento de arquivo associado com *fildes*. Antes do retorno bem sucedido do *write()*, o deslocamento de arquivo deve ser incrementado pelo número de bytes realmente escritos. Em um arquivo regular, se a posição do último byte escrito é maior ou igual ao comprimento do ficheiro, a duração do processo deve ser ajustado para esta posição mais um.

* Em um arquivo não é capaz de busca, a escrita deve ocorrer sempre começando na posição atual. O valor de um ficheiro de deslocamento associado com um tal dispositivo é indefinido.

* Se write() é interrompida por um sinal antes que ele escreve todos os dados, ele deve retornar -1 com errno definido para [EINTR].
* Se write() é interrompida por um sinal após escreve com sucesso alguns dados, ele deve retornar o número de bytes escritos.
* Se o valor de nbyte é maior do que *SSIZE_MAX{}*, o resultado é definido pela implementação.

* Qualquer sucesso *read()* de cada posição de byte no arquivo que foi modificado por essa gravação deve retornar os dados especificados pelo *write()* para essa posição até que tais posições de byte são novamente modificadas.

Após a conclusão, esta função deve retornar o número de bytes realmente gravados no arquivo associado com *fildes*. Este número nunca será maior do que *nbyte*. Caso contrário, -1 será retornado e *errno* ajustado para indicar o erro.