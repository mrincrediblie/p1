#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definicao Constantes */

#define VERDADE 1
#define FALSO 0
#define NAO_ENCONTRADO -1

#define ERRO_PARSING 1
#define MAX_TAMANHO_LINHA BUFSIZ

#define MAX_NOME_PARAGEM 51
#define MAX_NOME_CARREIRA 21

/* Definicao de Tipos de Dados */

typedef struct paragem Paragem;
typedef struct carreira Carreira;
typedef struct ligacao Ligacao;

struct paragem
{
    char *nome;
    double latitude, longitude;
    Carreira** carreiras;
    //int *idCarreiras;
    int numCarreiras;
    Paragem *prev;
    Paragem *next;
} ;

struct ligacao
{
    Carreira* carreira;
    Paragem* paragemOrigem, paragemDestino;
    double custo, duracao;
    Ligacao *prev;
    Ligacao *next;
} ;

struct carreira
{
    char *nome;
    double custoTotal;
    double duracaoTotal;
    // int idLigacoes[MAX_LIGACOES];
    Ligacao** ligacoes;
    int numLigacoes;
    Carreira *prev;
    Carreira *next;
} ;

/* Variaveis Globais */

char* _buffer; /* Buffer auxiliar. */

/* Variáveis para guardar paragens, ligações e carreiras. */

Paragem *listaParagens = NULL;
Paragem* tailListaParagens = NULL;
Ligacao *listaLigacoes = NULL;
Ligacao* tailListaLigacoes = NULL;
Carreira *listaCarreiras = NULL;
Carreira *tailListaCarreiras = NULL;


int leEspacos()
{
    int c;
    while ((c = getchar()) == ' ' || c == '\t')
        ;
    if (c == '\n')
        return 0;
    ungetc(c, stdin);
    return 1;
}
char* leNome()
{
    char* s = (char*) malloc(sizeof(char));
    int i = 0, c;
    s[0] = getchar();
    if (s[0] != '"')
    {
        i = 1;
        while ((c = getchar()) != ' ' && c != '\t' && c != '\n'){
            s = realloc(s, i + 1);
            s[i++] = c;
        }
        ungetc(c, stdin);
    }
    else
    {
        while ((c = getchar()) != '"'){
            s = realloc(s, i + 1);
            s[i++] = c;
        }
    }
    s[i++] = '\0';
    return s;
}
void leAteFinalLinha(char s[])
{
    char c;
    int i = 0;
    while ((c = getchar()) != '\n')
    {
        s[i++] = c;
    }
    s[i] = '\0';
}

void mostraParagem(Paragem *paragem)
{
    printf("%s: %16.12f %16.12f %d\n", paragem->nome, paragem->latitude,
           paragem->longitude, paragem->numCarreiras);
}

/* Mostra todas as paragens. */

void listaAsParagens(Paragem* listaParagens)
{
    Paragem *paragem = listaParagens;
    while (paragem != NULL)
    {
        mostraParagem(paragem);
        paragem = paragem->next;
    }
}

/* Verifica se existe uma paragem com um determinado nome.
   Se existir devolve o indice. Caso contrário, devolve NAO_ENCONTRADO. */

Paragem *encontraParagem(Paragem *listaParagens, char *nome)
{
    Paragem *p = listaParagens;
    while (p != NULL)
    {
        if (strcmp(p->nome, nome) == 0)
            return p;
        else
            p = p->next;
    }
    return NULL;
}
/* Cria uma nova paragem. */

void criaParagem(Paragem** head, Paragem** tail, char *nomeParagem, double latitude, double longitude)
{
    Paragem *novaParagem = (Paragem *)malloc(sizeof(Paragem));
    novaParagem->latitude = latitude;
    novaParagem->longitude = longitude;
    novaParagem->numCarreiras = 0;
    novaParagem->nome = (char*) malloc(sizeof(char) * (strlen(nomeParagem)+1));
    strcpy(novaParagem->nome, nomeParagem);
    novaParagem->carreiras = NULL;
    novaParagem->next = NULL;
    if (listaParagens == NULL){
        novaParagem->prev = NULL;
        listaParagens = novaParagem;
        *tail = novaParagem;
        printf("p esta vazio\n");
    }
    else {
        novaParagem->prev = *tail;
        (*tail)->next = novaParagem;
        *tail = novaParagem;
       
        
    }
    
}

/* Função para tratar o comando 'p'. */

void paragens()
{
    char* s = NULL;
    Paragem* p = NULL;
    int fimLinha = leEspacos();

    if (!fimLinha)
    {
        listaAsParagens(listaParagens);
        return;
    }
    s = leNome();
    fimLinha = leEspacos();
    if (!fimLinha)
    {
        if ((p = encontraParagem(listaParagens,s)) == NULL)
            printf("%s: no such stop.\n", s);
        else
            printf("%16.12f %16.12f\n", p->latitude, p->longitude);
    }
    else
    {
        double latitude, longitude;
        scanf("%lf%lf", &latitude, &longitude);
        if (encontraParagem(listaParagens,s) == NULL)
            criaParagem(&listaParagens,&tailListaParagens, s, latitude, longitude);
        else
            
        leAteFinalLinha(_buffer);
    }free(s);
}


//carreiras ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void mostraCarreira(Carreira* c)
{   printf("estou no mostra carreira");
    int numLigacoes = c->numLigacoes;

    printf("%s ", c->nome);
    if (numLigacoes > 0)
    { 
    printf("%s %s ", c->ligacoes[0]->paragemOrigem->nome,
                     c->ligacoes[numLigacoes-1]->paragemDestino.nome);
    printf("%d ", numLigacoes+1);
    printf("%.2f ", c->custoTotal);
    printf("%.2f\n", c->duracaoTotal);
    }
    else 
        printf("%d %.2f %.2f\n", 0, 0.0, 0.0);
    /*
    if (numLigacoes > 0)
    {
        printf("%s %s ", _paragens[_ligacoes[_carreiras[i].idLigacoes[0]].idOrigem].nome,
               _paragens[_ligacoes[_carreiras[i].idLigacoes[numLigacoes - 1]].idDestino].nome);
        printf("%d ", numLigacoes + 1);
        printf("%.2f ", _carreiras[i].custoTotal);
        printf("%.2f\n", _carreiras[i].duracaoTotal);
    }
    else
        printf("%d %.2f %.2f\n", 0, 0.0, 0.0);
    */

}


/* Mostra as ligações da carreira com indice i. */

void mostraLigacoesCarreira(Carreira *c, int inverso)
{

    Ligacao *ligacao = NULL;
    int numLigacoes = c->numLigacoes, i;

    if (numLigacoes == 0)
        return;
    if (inverso == FALSO)
    {
        for (i = 0; i < numLigacoes; i++)
        {
            ligacao = c->ligacoes[i];
            printf("%s, ", ligacao->paragemOrigem->nome);
        }
        ligacao = c->ligacoes[numLigacoes - 1];
        printf("%s\n", ligacao->paragemDestino.nome);
    }
    else
    {
        for (i = numLigacoes - 1; i >= 0; i--)
        {   
            ligacao = c->ligacoes[i];
            printf("%s, ", ligacao->paragemDestino.nome);
            
        }
        ligacao = c->ligacoes[0];
        printf("%s\n", ligacao->paragemOrigem->nome);
    }
}

/* Mostra todas as carreiras. */

void listaAsCarreiras(Carreira* listaCarreiras)
{
    Carreira* c = listaCarreiras;
    while (c != NULL)
    {
        mostraCarreira(c);
        c = c->next;
    }

}


Carreira* encontraCarreira(Carreira* listaCarreiras, char nome[]) { 
    
    Carreira *c = listaCarreiras;
    while (c != NULL)
    {
        if (strcmp(c->nome, nome) == 0)
            return c;
        else
            c = c->next;
    }
    return NULL;
}



/*Paragem *encontraParagemCarreira(Carreira* c, Paragem* p)
{
    int numLigacoes = _carreiras[idCarreira].numLigacoes;
    int i, idLigacao;

    for (i = 0; i < numLigacoes; i++)
    {
        idLigacao = _carreiras[idCarreira].idLigacoes[i];
        if (_ligacoes[idLigacao].idOrigem == idParagem)
            return i;
    }
    idLigacao = _carreiras[idCarreira].idLigacoes[numLigacoes - 1];
    if (_ligacoes[idLigacao].idDestino == idParagem)
        return numLigacoes;
    return NAO_ENCONTRADO;
}
Cria uma carreira nova. */

void criaCarreira(Carreira** head, Carreira** tail, char nomeCarreira[])
{
    printf("estou no criaCarreira\n");
    Carreira *novaCarreira = (Carreira*) malloc(sizeof(Carreira));
    if (novaCarreira == NULL)
    {
        printf("Erro ao criar nova carreira\n");
        return;
    }
    strcpy(novaCarreira->nome, nomeCarreira);
    novaCarreira->custoTotal = 0.0;
    novaCarreira->duracaoTotal = 0.0;
    novaCarreira->numLigacoes = 0;
    novaCarreira->ligacoes = NULL;
    novaCarreira->next = NULL;
    if (listaCarreiras == NULL){
        novaCarreira->prev = NULL;
        listaCarreiras = novaCarreira;
        *tail = novaCarreira;
        printf("p esta vazio\n");
       
    }
    else {
        novaCarreira->prev = *tail;
        (*tail)->next = novaCarreira;
        *tail = novaCarreira;
        
    }
     
}

/* Verifica se a string é um prefixo de tamanho pelo menos 3 da
   palavra inverso. */

int verificaInversoOk(char s[])
{
    char inv[] = "inverso";
    int size = strlen(s), i;

    if (size < 3 || size > 7)
        return FALSO;
    for (i = 0; i < size; i++)
        if (inv[i] != s[i])
            return FALSO;
    return VERDADE;
}

/* Função para tratar do comando 'c'. */

void carreiras()
{
    char* s = NULL;
    Carreira *c = NULL;
    int fimLinha = leEspacos();

    if (!fimLinha)
    {
        listaAsCarreiras(listaCarreiras);
        return;
    }

    s = leNome();
    c = encontraCarreira(listaCarreiras, s);
    fimLinha = leEspacos();
    if (!fimLinha)
    {
        if ((c = encontraCarreira(listaCarreiras, s)) == NULL)
            criaCarreira(&listaCarreiras, &tailListaCarreiras, s);
        else
            mostraLigacoesCarreira(c, FALSO);
    }
    else
    {
        _buffer = leNome();
        if (verificaInversoOk(_buffer))
        {
            if (c == NULL)
            {
                printf("invalid bus line\n");
                return;
            }
            mostraLigacoesCarreira(c, VERDADE);
        }
        else
            printf("incorrect sort option.\n");
        leAteFinalLinha(_buffer);
    }
    free(s);
    free(_buffer);
    
}



int main()
{
    int c;

    do
    {
        c = getchar();
        switch (c)
        {
        case 'c':
            carreiras();
            break;
        case 'p':
            paragens();
            break;
        case 'l':
            
            break;
        case 'i':
            
            break;
        case 'q':
            break;
        default:
            /* Ignorar linhas em branco */
            if (c == ' ' || c == '\t' || c == '\n')
                break;
        }
    } while (c != 'q');
    return 0;
}
