#include "agenda.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    lista lst,retorno;
    no valor;
    int posicao,ctrl = 1,acao;
    int *telefone;
    char nome[20];

    //criando a lista
    criar(&lst);

    while(ctrl)
    {
        menu();

        printf("- Informe sua acao: ");
        scanf("%d%*c",&acao);

        switch(acao)
        {
            case 1: 
                printf("\n## INFORMACOES DO CONTATO: \n\n");
                printf("Posicao: ");
                scanf("%d%*c",&posicao);
                printf("Nome: ");
                scanf("%[^\n]s",valor.nome);
                printf("Telefone: ");
                scanf("%*c%d",&valor.telefone);
                printf("Email [seunome@email.com]: ");
                scanf("%s",valor.email);
                printf("Data Nasc. [dd/mm/aaaa]: ");
                scanf("%d/%d/%d%*c",&valor.dt_nascimento.dia,&valor.dt_nascimento.mes,&valor.dt_nascimento.ano);

                if(inserir(&lst,posicao,valor))
                    printf("\n>> Contato inserido com sucesso! <<\n\n");
                else 
                    printf("\n>> Ops, nao foi possivel inserir o contato! <<\n\n");
                break;

            case 2:
                printf("\n## INFORMACOES DO CONTATO: \n\n");
                printf("Posicao: ");
                scanf("%d%*c",&posicao);
                printf("Nome: ");
                scanf("%[^\n]s",valor.nome);
                printf("Telefone: ");
                scanf("%*c%d",&valor.telefone);
                printf("Email: (seunome@email.com)");
                scanf("%s",valor.email);
                printf("Data Nasc. [dd/mm/aaaa]: ");
                scanf("%d/%d/%d%*c",&valor.dt_nascimento.dia,&valor.dt_nascimento.mes,&valor.dt_nascimento.ano);

                if(atualizar(&lst,posicao,valor))
                    printf("\n>> Contato atualizado com sucesso! <<\n\n");
                else 
                    printf("\n>> Ops, nao foi possivel atualizar o contato! <<\n\n");
                break;

            case 3: 
                printf("\n## CONTATO QUE SERA EXCLUIDO: \n\n");
                printf("Posicao: ");
                scanf("%d%*c",&posicao);

                if(remover(&lst,posicao,telefone))
                    printf("\n>> Contato removido com sucesso! <<\n\n");
                else 
                    printf("\n>> Ops, nao foi possivel remover o contato! <<\n\n");
                break;

            case 4: 
                printf("\n## CONTATO QUE SERA PESQUISADO: \n\n");
                printf("Nome: ");
                scanf("%[^\n]s",nome);
                getchar();

                if(busca(lst,nome))
                    printf("\n>> Contato existe! <<\n\n");
                else 
                    printf("\n>> Ops, nao foi possivel achar o contato! <<\n\n");
                break;

            case 5:
                printf("\n## TODOS OS CONTATOS: \n\n");
                imprime(lst);
                break;

            case 6:
                limpar(&lst);
                printf("\n>> Todos os contatos foram excluidos! <<\n\n");
                break;

            case 7:
                if(vazia(lst))
                    ctrl = 0;
                else   
                    printf("\n>> Ainda ha registro(s) na agenda, apague antes de sair! <<\n\n"); 
                break;

            default: 
                printf("\n>> Acao invalida! <<\n\n");
        }
        system("pause");
        system("cls");
    }


    return 0;
}