/**
 * Funcoes para criacao de pilhas para nos de arvores.
 */
#include "conversor.h"

typedef struct stno {
    tno *leaf;
    struct stno *prox;
} nop;

typedef nop* pilha;

void criarPilha(pilha *p);
int pilhaVazia(pilha p);
int pilhaTamanho(pilha p);
int empilhar(pilha *p, tab *leaf);
int desempilhar(pilha *p, tab *arv);
int topo(pilha p, tab *arv);
void imprimePilha(pilha p);
void esvaziarPilha(pilha *p);
int buscaPilha(pilha p, telem dado);

/**
 * Funcoes para criacao de pilhas para float.
 */
typedef struct stnopv {
    float dado;
    struct stnopv *prox;
} nopv;

typedef nopv* vpilha;

void criarIPilha(vpilha *p);
int vpilhaVazia(vpilha p);
int vpilhaTamanho(vpilha p);
int empilharV(vpilha *p, float dado);
int desempilharV(vpilha *p, float *dado);
int topoPilhaV(vpilha p, float *dado);
void imprimeVPilha(vpilha p);
void esvaziarVPilha(vpilha *p);
