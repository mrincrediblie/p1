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
    //int *cs;
    int numCarreiras;
    Paragem *prev;
    Paragem *next;
} ;

struct ligacao
{
    Carreira* carreira;
    Paragem* paragemOrigem;
    Paragem* paragemDestino;
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
    if (*head == NULL) {
        novaParagem->prev = NULL;
        *head = novaParagem;
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
                     c->ligacoes[numLigacoes-1]->paragemDestino->nome);
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
        printf("%s\n", ligacao->paragemDestino->nome);
    }
    else
    {
        for (i = numLigacoes - 1; i >= 0; i--)
        {   
            ligacao = c->ligacoes[i];
            printf("%s, ", ligacao->paragemDestino->nome);
            
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



int encontraParagemCarreira(Carreira* c, Paragem* p)
{
    int numLigacoes = c->numLigacoes;
    int i;
    Ligacao* ligacao = NULL;

    for (i = 0; i < numLigacoes; i++)
    {
        ligacao = c->ligacoes[i];
        if (ligacao->paragemOrigem == p)
            return i;
    }
    ligacao = c->ligacoes[numLigacoes - 1];
    if (ligacao->paragemDestino == p)
        return numLigacoes;
    return NAO_ENCONTRADO;
}


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
//Ligacao-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void criaLigacao(Ligacao** head, Ligacao** tail, Carreira* c,
            Paragem* pOrigem, Paragem* pDestino, double custo, double duracao) {  

    Ligacao* novaLigacao = (Ligacao*) malloc(sizeof(Ligacao));
    novaLigacao->carreira = c;
    novaLigacao->paragemOrigem = pOrigem;
    novaLigacao->paragemDestino = pDestino;
    novaLigacao->custo = custo;
    novaLigacao->duracao = duracao;
    if (*head == NULL) {
        novaLigacao->prev = NULL;
        *head = novaLigacao;
        *tail = novaLigacao;
    }
    else {
        novaLigacao->prev = *tail;
        (*tail)->next = novaLigacao;
        *tail = novaLigacao; 
    }
}

/* Acrescenta uma nova ligação no fim de uma carreira. */

void acrescentaLigacaoFim(Carreira* carreira, Ligacao* ligacao) {
    if (carreira->ligacoes == NULL) {
        carreira->ligacoes = (Ligacao**) malloc(sizeof(ligacao));
        carreira->ligacoes[0] = ligacao;
    }

    else {
        int numLigacoes = carreira->numLigacoes;
        carreira->ligacoes = (Ligacao**) realloc(carreira->ligacoes, (numLigacoes+1) * sizeof(Ligacao));
        carreira->ligacoes[numLigacoes] = ligacao;
    }
    carreira->numLigacoes++;
    
}
/* Acrescenta uma nova ligação no início de uma carreira. */

void acrescentaLigacaoInicio(Carreira* carreira, Ligacao* ligacao) {
    
    if (carreira->ligacoes == NULL) {
        carreira->ligacoes = (Ligacao**) malloc(sizeof(Ligacao));
        carreira->ligacoes[0] = ligacao;
    }
    else {
        int numLigacoes = carreira->numLigacoes;
        carreira->ligacoes = (Ligacao**) realloc(carreira->ligacoes, (numLigacoes+1) * sizeof(Ligacao));
        for (int i = numLigacoes; i > 0; i--) {
            carreira->ligacoes[i] = carreira->ligacoes[i-1];
        }
        carreira->ligacoes[0] = ligacao;
    }
    carreira->numLigacoes++;
}

void adicionaCarreiraParagem(Paragem* paragem, Carreira* carreira) {
    int i;
    for (i = 0; i < paragem->numCarreiras; i++) {
        if (strcmp(paragem->carreiras[i]->nome, carreira->nome)) {
            printf("AVISO: paragem ja associada a carreira.\n");
            return;
        }
    }
    paragem->carreiras = (Carreira**) realloc(paragem->carreiras, (paragem->numCarreiras+1) * sizeof(Carreira));
    paragem->carreiras[paragem->numCarreiras] = carreira;
    paragem->numCarreiras++;
    /*
    _paragens[idParagem].cs[_paragens[idParagem].numCarreiras] = c;
    _paragens[idParagem].numCarreiras++;
    */
}

void adicionaPrimeiraLigacao(Ligacao** head, Ligacao** tail, Carreira* c, Paragem* pOrigem, Paragem* pDestino, double custo, double duracao) {

    adicionaCarreiraParagem(pOrigem, c);
    if (pOrigem != pDestino)
        adicionaCarreiraParagem(pDestino, c);
    criaLigacao(head, tail, c, pOrigem, pDestino, custo, duracao);
    acrescentaLigacaoFim(c, *tail);
}

void adicionaLigacao(Ligacao** head, Ligacao** tail, Carreira* c, Paragem* pOrigem, Paragem* pDestion,
                     double custo, double duracao)
{
    int numLigacoesCarreira = c->numLigacoes;

    if (numLigacoesCarreira == 0)
        adicionaPrimeiraLigacao(&listaLigacoes, &tailListaLigacoes, c, pOrigem, pDestion,
                                custo, duracao);
    else
    {
        Ligacao* primeiraLigacao = *c->ligacoes;
        Ligacao* ultimaLigacao = c->ligacoes[numLigacoesCarreira - 1];
        if (pOrigem == ultimaLigacao->paragemDestino)
        {
            if (encontraParagemCarreira(c, pDestion) == NAO_ENCONTRADO)
                adicionaCarreiraParagem(pDestion, c);
            criaLigacao(head, tail, c, pOrigem, pDestion, custo, duracao);
            acrescentaLigacaoFim(c, *tail);
        }
        else if (pDestion == ultimaLigacao->paragemOrigem)
        {
            if (encontraParagemCarreira(c, pOrigem) == NAO_ENCONTRADO)
                adicionaCarreiraParagem(pOrigem, c);
            criaLigacao(head, tail, c, pOrigem, pDestion, custo, duracao);
            acrescentaLigacaoInicio(c, *tail);
        }
        else
            printf("link cannot be associated with bus line.\n");
    }
}

/*void leNomesComando(char nomeCarreira[], char nomeOrigem[], char nomeDestino[])
{   
    leEspacos();
    leNome(nomeCarreira);
    leEspacos();
    leNome(nomeOrigem);
    leEspacos();
    leNome(nomeDestino);
}
*/
void ligacoes()
{
    char* nomeCarreira;
    char*  nomeOrigem;
    char* nomeDestino;
    double custo, duracao;
    Carreira* carreira;
    Paragem* pOrigem;
    Paragem* pDestino;

    leEspacos();
    nomeCarreira = leNome();
    leEspacos();
    nomeOrigem = leNome();
    leEspacos();
    nomeDestino = leNome();

    //leNomesComando(nomeCarreira, nomeOrigem, nomeDestino);
    scanf("%lf%lf", &custo, &duracao);
    leAteFinalLinha(_buffer);

    carreira = encontraCarreira(listaCarreiras,nomeCarreira);
    if (carreira == NULL)
        printf("%s: no such line.\n", nomeCarreira);
    else
    {
        pOrigem = encontraParagem(listaParagens, nomeOrigem);
        if (pOrigem == NULL)
            printf("%s: no such stop.\n", nomeOrigem);
        else
        {
            pDestino = encontraParagem(listaParagens, nomeDestino);
            if (pDestino == NULL)
                printf("%s: no such stop.\n", nomeDestino);
            else if (custo < 0.0 || duracao < 0.0)
                printf("negative cost or duration.\n");
            else
                adicionaLigacao(&listaLigacoes, &tailListaLigacoes, carreira, pOrigem, pDestino, custo, duracao);
        }
    }
}

void apaga(){
    Paragem* p = NULL;
    while(p != NULL){
        p = listaParagens;
        if (p->next == NULL)
            free(p);
        listaParagens = listaParagens->next;
        free(p);
    }
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
            ligacoes();
            break;
        case 'i':
            
            break;
        case 'q':
            apaga();
            break;
        default:
            /* Ignorar linhas em branco */
            if (c == ' ' || c == '\t' || c == '\n')
                break;
        }
    } while (c != 'q');
    return 0;
}
