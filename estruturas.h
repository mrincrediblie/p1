/* iaed-23 - ist1103580 - project2 */

#ifndef _ESTRUTURAS_H_
#define _ESTRUTURAS_H_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define VERDADE 1
#define FALSO 0
#define NAO_ENCONTRADO -1

#define ERRO_PARSING 1
#define MAX_TAMANHO_LINHA BUFSIZ


/* Declaracao das estruturas */

typedef struct paragem Paragem;
typedef struct carreira Carreira;
typedef struct ligacao Ligacao;
typedef struct sistema Sistema;

struct sistema {
    Paragem *listaParagens;
    Paragem *tailListaParagens;
    Carreira *listaCarreiras;
    Carreira *tailListaCarreiras;
    Ligacao *listaLigacoes;
    Ligacao *tailListaLigacoes;
};

struct paragem
{
    char *nome;
    double latitude, longitude;
    Carreira **carreiras;

    int numCarreiras;
    Paragem *prev;
    Paragem *next;
};

struct ligacao
{
    Carreira *carreira;
    Paragem *paragemOrigem;
    Paragem *paragemDestino;
    double custo, duracao;
    Ligacao *prev;
    Ligacao *next;
};

struct carreira
{
    char *nome;
    double custoTotal;
    double duracaoTotal;
    /*int idLigacoes[MAX_LIGACOES];*/
    Ligacao **ligacoes;
    int numLigacoes;
    Carreira *prev;
    Carreira *next;
};


/* Prototipos das funcoes */

void inicializarSistema(Sistema *sistema);

int leEspacos();

char* leNome();

void leAteFinalLinha(char s[]);

#endif
