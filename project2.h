/* iaed-23 - ist1103580 - project2 */

#ifndef _PROJECT2_H_
#define _PROJECT2_H_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "estruturas.h"

/* Prototipos das funcoes relativas as paragens */

Paragem *encontraParagem(Paragem *listaParagens, char *nome) ;

void criaParagem(Sistema* s, char *nomeParagem, double latitude, double longitude);

void mostraParagem(Paragem *paragem);

void listaAsParagens(Paragem *listaParagens);


/* Prototipos das funcoes relativas as carreiras */

void mostraCarreira(Carreira *c);

void criaCarreira(Sistema* s, char *nomeCarreira);

void removeCarreiraParagens(Carreira *carreira, Paragem *paragens);

void eliminaLigacaoCarreira(Sistema* s, Paragem* p);

void mostraLigacoesCarreira(Carreira *c, int inverso);

void listaAsCarreiras(Carreira *listaCarreiras);

Carreira *encontraCarreira(Carreira *listaCarreiras, char *nome);

int encontraParagemCarreira(Carreira *c, Paragem *p);

int verificaInversoOk(char s[]);


/* Prototipos das funcoes relativas as ligacoes */

void criaLigacao(Ligacao **head, Ligacao **tail, Carreira *c, Paragem *pOrigem, 
                 Paragem *pDestino, double custo, double duracao);

Ligacao* encontraLigacao(Ligacao **head, Carreira *c, Paragem *pOrigem, 
                         Paragem *pDestino, double custo, double duracao);

void removeLigacoesComCarreira(Ligacao **ligacoes, Ligacao ** tailLigacoes, 
                               Carreira *carreira);
    
void apagaLigacao(Sistema* s, Ligacao* ligacao);

void acrescentaLigacaoFim(Carreira *carreira, Ligacao *ligacao);

void acrescentaLigacaoInicio(Carreira *carreira, Ligacao *ligacao);

void adicionaCarreiraParagem(Paragem *paragem, Carreira *carreira);

void adicionaPrimeiraLigacao(Ligacao **head, Ligacao **tail, Carreira *c, 
            Paragem *pOrigem, Paragem *pDestino, double custo, double duracao);

void adicionaLigacao(Sistema* s, Carreira *c, Paragem *pOrigem, Paragem *pDestion,
                     double custo, double duracao);


/* Funcao de ordenacao para as intersecoes */
void ordenaCarreiras(Carreira **carreiras, int numCarreiras);


/* --------------------- Funcoes para comandos --------------------- */

/* comando p */
void paragens(Sistema *sistema);

/* comando c */
void carreiras(Sistema *sistema);

/*comando l */
void ligacoes(Sistema* s);

/*comando i */
void intersecoes(Sistema* s);

/*comando r */
void apagaCarreira(Sistema* s); 

/*comando e */
void apagaParagem(Sistema* s);

/* comando a */

void apagaParagens(Sistema* sistema);

void apagaCarreiras(Sistema* sistema);

void apagaLigacoes(Sistema* sistema);

void apagaSistema(Sistema* sistema);

#endif
