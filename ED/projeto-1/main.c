#include "agenda.h"
#include <stdio.h>
#include <string.h>

int main()
{
    lista lst,retorno;
    no valor;
    int posicao;
    int *telefone;

    //iniciando dados
    strcpy(valor.nome,"Ronily segundo");
    valor.telefone = 12345;
    strcpy(valor.email,"teste@teste.com");
    valor.dt_nascimento.dia = 1;
    valor.dt_nascimento.mes = 2;
    valor.dt_nascimento.ano = 2015;

    //criando a lista
    criar(&lst);

    //inserindo 1º elemento na posicao 1
    inserir(&lst,1,valor);

    //iniciando dados do segundo elemento
    strcpy(valor.nome,"Ronily primeiro");
    valor.telefone = 123456;
    strcpy(valor.email,"teste@teste.com");
    valor.dt_nascimento.dia = 1;
    valor.dt_nascimento.mes = 2;
    valor.dt_nascimento.ano = 2015;

    //inserindo 2º elemento na primeira posicao
    //if( !inserir(&lst,1,valor) ){ printf("Telefone ja cadastrado!\n"); }

    // apartir daqui caso queira ver funcionando alguns teste , eh so tirar o comentario - by Ronily

    //elemento(lst,1,&retorno);
    //printf("elemento.nome = %s\n", retorno->nome);

    //if(busca(lst,"Ronily primeiro")) printf("busca deu certo\n");
    //else printf("deu errado\n");

    /*
    strcpy(valor.nome,"Editado");
    valor.telefone = 9999;
    strcpy(valor.email,"editado@editado.com");
    valor.dt_nascimento.dia = 999;
    valor.dt_nascimento.mes = 999;
    valor.dt_nascimento.ano = 999;
    atualizar(&lst,1,valor);
    */

    printf("\n\n");

    //menu();

    printf("\n\n");

    imprime(lst);

    //printf("%d",busca(lst,"ROnily GOmes"));

    //limpar(&lst);

    //printf("%d vazia\n", vazia(lst));

    //printf("tamanho = %d\n", tamanho(lst));

    //inserir(&lst,2,valor);
    //inserir(&lst,3,valor);

    //remover(&lst,2,telefone);
    //printf("%d\n", *telefone);

    //printf("tamanho = %d\n", tamanho(lst));

    system("pause");

    return 0;
}
