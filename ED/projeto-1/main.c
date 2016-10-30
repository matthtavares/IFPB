/**
 * Programa criado como primeiro projeto para
 * a disciplina de Estrutura de Dados do IFPB.
 *
 * https://github.com/matthtavares/IFPB/tree/master/ED/projeto-1
 *
 * @author  Ronily Gomes  <ronilyweb@gmail.com>
 * @author  Mateus Tavares  <mateus460@gmail.com>
 */

#include "agenda.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    lista lst, retorno;
    no valor;
    int posicao, ctrl = 1, acao, i, erro = 0, telefone;
    char nome[20], phone[50];

    //criando a lista
    criar(&lst);

    while(ctrl)
    {
        menu();

        printf("- Informe sua acao: ");
        scanf("%d%*c", &acao);

        switch(acao)
        {
            case 1: 
                printf("\n## INFORMACOES DO CONTATO: \n\n");
                printf("Posicao: ");
                scanf("%d%*c", &posicao);
                printf("Nome: ");
                scanf("%[^\n]s", valor.nome);
                printf("Telefone: ");
                scanf("%s", phone);

                erro = 0;
                for(i = 0; phone[i] != '\0'; ++i){
                    if(!isdigit(phone[i])){
                        erro++;
                        break;
                    }
                }

                if( erro > 0 ){
                    printf("\nTelefone invalido!\n\n");
                    break;
                }else valor.telefone = atoi(phone);

                printf("Email [seunome@email.com]: ");
                scanf("%s", valor.email);
                printf("Data Nasc. [dd/mm/aaaa]: ");
                scanf("%d/%d/%d%*c", &valor.dt_nascimento.dia, &valor.dt_nascimento.mes, &valor.dt_nascimento.ano);

                if(inserir(&lst, posicao, valor))
                    printf("\n>> Contato inserido com sucesso! <<\n\n");
                else 
                    printf("\n>> Ops, nao foi possivel inserir o contato! <<\n\n");
                break;

            case 2:
                printf("\n## INFORMACOES DO CONTATO: \n\n");
                printf("Posicao: ");
                scanf("%d%*c", &posicao);
                printf("Nome: ");
                scanf("%[^\n]s", valor.nome);
                printf("Telefone: ");
                scanf("%s", phone);

                erro = 0;
                for(i = 0; phone[i] != '\0'; ++i){
                    if(!isdigit(phone[i])){
                        erro++;
                        break;
                    }
                }

                if( erro > 0 ){
                    printf("\nTelefone invalido!\n\n");
                    break;
                }else valor.telefone = atoi(phone);

                printf("Email [seunome@email.com]: ");
                scanf("%s", valor.email);
                printf("Data Nasc. [dd/mm/aaaa]: ");
                scanf("%d/%d/%d%*c", &valor.dt_nascimento.dia, &valor.dt_nascimento.mes, &valor.dt_nascimento.ano);

                if(atualizar(&lst, posicao, valor))
                    printf("\n>> Contato atualizado com sucesso! <<\n\n");
                else 
                    printf("\n>> Ops, nao foi possivel atualizar o contato! <<\n\n");
                break;

            case 3: 
                printf("\n## CONTATO QUE SERA EXCLUIDO: \n\n");
                printf("Posicao: ");
                scanf("%d%*c", &posicao);

                if(remover(&lst, posicao, &telefone)){
                    printf("\n>> Contato removido com sucesso! <<\n");
                    printf("\n>> Seu telefone era: %d <<\n\n", telefone);
                }else{
                    printf("\n>> Ops, nao foi possivel remover o contato! <<\n\n");
                }
                break;

            case 4: 
                printf("\n## CONTATO QUE SERA PESQUISADO: \n\n");
                printf("Digite a posicao do contato: ");
                scanf("%d", &posicao);

                if( listar(lst, posicao) ){
                	elemento(lst, posicao, &retorno);
                	valor = *retorno;
                	printf("\n");
                	printf("Nome: %s\n", valor.nome);
					printf("Email: %s\n", valor.email);
					printf("Telefone: %d\n", valor.telefone);
					printf("Data de Nascimento: %d/%d/%d\n\n", valor.dt_nascimento.dia, valor.dt_nascimento.mes, valor.dt_nascimento.ano);
				}else{
                	printf("\n>> Ops, nao foi encontrado nenhum contato! <<\n\n");
				}
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