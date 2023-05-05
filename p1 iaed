/* iaed-23 - ist1103580 - project1 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCARREIRAS 200  /* número máximo de carreiras */
#define MAXPARAGENS 10000 /* número máximo de paragens */
#define MAXLIGACOES 30000 /* número máximo de ligações */

#define MAXNOMECARREIRA 21 /* dimensão máxima do nome das carreiras */
#define MAXNOMEPARAGEM 51  /* dimensão máxima do nome das paragens */
#define TRUE 1             /* verdadeiro */
#define FALSE 0            /* falso */

/*Tipos de Dados*/

typedef struct
{
    char nome[MAXNOMEPARAGEM];
    double lat;
    double lon;
} Paragem;

typedef struct
{
    char nome[MAXNOMECARREIRA];
    int paragens[MAXPARAGENS];
    int num_paragens;
    float custo;
    float duracao;
} Carreira;

/* Variaveis globais */

int num_carreiras = 0;            /* numero de carreias introduzidas */
Carreira carreiras[MAXCARREIRAS]; /* vetor de carreiras */

int num_paragens = 0;          /* numero de paragens introduzidas */
Paragem paragens[MAXPARAGENS]; /* vetor de paragens */

int num_ligacoes = 0; /* numero de ligacoes introduzidas */

/* Funcoes relacionadas a Paragens------------------------ */

int valida_paragem_existe(char *nome)
{
    int i;
    if (num_paragens > 0)
    {
        for (i = 0; i < num_paragens; i++)
        {
            if (strcmp(nome, paragens[i].nome) == 0)
                return TRUE;
        }
    }
    return FALSE;
}

void cria_paragem(char nome[])
{
    double lat, lon;
    scanf("%lf %lf", &lat, &lon);
    strcpy(paragens[num_paragens].nome, nome);
    paragens[num_paragens].lat = lat;
    paragens[num_paragens].lon = lon;
    num_paragens++;
}

/* esta funcao retorna o indice da paragem no vetor paragens */
int devole_o_indice_da_paragem_pelo_nome(char *nome)
{

    int i;
    int result = 0;

    for (i = 0; i < num_paragens; i++)
    {
        if (strcmp(nome, paragens[i].nome) == 0)
            result = i;
    }
    return result;
}

int valida_paragem_existe_na_carreira_pelo_nome(Carreira c, char *nome)
{
    int i, n = c.num_paragens;
    int indice = devole_o_indice_da_paragem_pelo_nome(nome);

    for (i = 0; i < n; i++)
    {
        if (c.paragens[i] == indice)
            return TRUE;
    }
    return FALSE;
}

/* esta funcao retorna a quantidade de carreiras que contenham a paragem */
int numero_de_carreiras_com_paragem(char *nome)
{
    int i, result = 0;

    for (i = 0; i < num_carreiras; i++)
    {
        if(valida_paragem_existe_na_carreira_pelo_nome(carreiras[i],nome)==TRUE)
            result++;
    }
    return result;
}

void escreve_lat_e_long_de_paragem(char *nome)
{
    int i;

    for (i = 0; i < num_paragens; i++)
    {
        if (strcmp(paragens[i].nome, nome) == 0)
        {
            printf("%16.12f %16.12f\n", paragens[i].lat, paragens[i].lon);
            return;
        }
    }
}

/* esta funcao destina-se a ler a proxima sring da linha de comando e verifica
 se é a ultima */
int le_a_proxima_palavra(char *str)
{

    char c = getchar();
    int i = 0;
    while (c == ' ' || c == '\t')
        c = getchar();

    if (c == '"')
    {
        c = getchar();
        while (c != '\t' && c != '\n' && c != '"')
        {
            str[i++] = c;
            c = getchar();
        }
        c = getchar();
    }
    else
    {
        while (c != ' ' && c != '\t' && c != '\n')
        {
            str[i++] = c;
            c = getchar();
        }
    }
    str[i] = '\0';

    return (c == '\n');
}

void lista_todas_paragens()
{
    int i;

    for (i = 0; i < num_paragens; i++)
    {
        int n = numero_de_carreiras_com_paragem(paragens[i].nome);
        printf("%s: %16.12f %16.12f %d\n", paragens[i].nome, paragens[i].lat,
               paragens[i].lon, n);
    }
}

void adiciona_e_lista_paragens()
{
    char p[MAXNOMEPARAGEM];
    int ultima = 0;
    ultima = le_a_proxima_palavra(p);
    if (strlen(p) == 0)
        lista_todas_paragens();
    else
    {
        if (ultima == 1)
        {

            if (valida_paragem_existe(p) == TRUE)
                escreve_lat_e_long_de_paragem(p);
            else
                printf("%s: no such stop.\n", p);
        }
        else
        {

            if (valida_paragem_existe(p) == FALSE)
            {

                if (num_paragens < MAXPARAGENS)
                    cria_paragem(p);
            }
            else
                printf("%s: stop already exists.\n", p);
        }
    }
}

/* Funcoes relacionadas a carreira ----------------------------*/

int valida_carreira_existe(char *nome)
{
    int i;
    if (num_carreiras > 0)
    {
        for (i = 0; i < num_carreiras; i++)
        {
            if (strcmp(carreiras[i].nome, nome) == 0)
                return TRUE;
        }
    }
    return FALSE;
}

/* esta carreira devolve-me um ponteiro para a carreira de modo a que eu possa
manipula-la diretamente */
Carreira *encontra_carreira(char *nome)
{

    Carreira *c = NULL;
    int i;

    for (i = 0; i < num_carreiras; i++)
    {
        if (strcmp(carreiras[i].nome, nome) == 0)
            c = &carreiras[i];
    }
    return c;
}

void cria_carreira(char *nome)
{
    strcpy(carreiras[num_carreiras].nome, nome);
    carreiras[num_carreiras].num_paragens = 0;
    carreiras[num_carreiras].custo = 0;
    carreiras[num_carreiras].duracao = 0;
    num_carreiras++;
}

void lista_carreira(char *nome)
{
    Carreira *c = NULL;
    int i, tamanho;
    c = encontra_carreira(nome);
    tamanho = c->num_paragens;
    if (tamanho != 0)
    {
        for (i = 0; i < tamanho - 1; i++)
            printf("%s, ", paragens[c->paragens[i]].nome);
        printf("%s\n", paragens[c->paragens[i]].nome);
    }
}

void lista_carreira_inverso(char *nome)
{
    Carreira *c = NULL;
    int i, tamanho;
    c = encontra_carreira(nome);
    tamanho = c->num_paragens;
    if (tamanho != 0)
    {
        for (i = (tamanho - 1); i > 0; i--)
            printf("%s, ", paragens[c->paragens[i]].nome);
        printf("%s\n", paragens[c->paragens[i]].nome);
    }
}

void lista_todas_carreiras()
{
    int i;

    for (i = 0; i < num_carreiras; i++)
    {
        if (carreiras[i].num_paragens > 0)
            printf("%s %s %s %d %.2f %.2f\n", carreiras[i].nome,
            paragens[carreiras[i].paragens[0]].nome,
            paragens[carreiras[i].paragens[carreiras[i].num_paragens - 1]].nome,
           carreiras[i].num_paragens, carreiras[i].custo, carreiras[i].duracao);
        else
            printf("%s %d %.2f %.2f\n", carreiras[i].nome,
                   carreiras[i].num_paragens, carreiras[i].custo,
                   carreiras[i].duracao);
    }
}

void getNomeCarreira(char *nome)
{
    int i = 0;
    char c = getchar();

    while (c == ' ')
        c = getchar();

    while (c != ' ' && c != EOF && c != '\n' && i < MAXNOMEPARAGEM - 1)
    {
        nome[i++] = c;
        c = getchar();
    }

    nome[i] = '\0';
}

void adiciona_e_lista_as_carreiras()
{
    char carreira[MAXNOMECARREIRA], sort[8];
    int ultima = 0;
    ultima = le_a_proxima_palavra(carreira);
    if (strlen(carreira) == 0) {
        lista_todas_carreiras();
    }
    else {
        if (ultima == 1) {
            if (valida_carreira_existe(carreira) == TRUE)
                lista_carreira(carreira);
            else if (num_carreiras < MAXCARREIRAS)
                cria_carreira(carreira);
        }
        else {
            getNomeCarreira(sort);
            if ((strcmp(sort, "inverso") == 0) || (strcmp(sort, "invers") == 0) 
            || (strcmp(sort, "inver") == 0) || (strcmp(sort, "inve") == 0 || 
            (strcmp(sort, "inv") == 0)))
            {
                if (valida_carreira_existe(carreira) == TRUE)
                    lista_carreira_inverso(carreira);
            }
            else
                printf("incorrect sort option.\n");
        }
    }
}

/* Funcoes relacionadas a Ligacao----------------------------- */

void adiciona_paragem_ao_fim_carreira(char *nome_carreira, char *nome_paragem)
{

    int i, n = devole_o_indice_da_paragem_pelo_nome(nome_paragem);

    for (i = 0; i < num_carreiras; i++)
    {
        if (strncmp(carreiras[i].nome, nome_carreira, MAXNOMECARREIRA - 1) == 0)
        {
            if (carreiras[i].num_paragens < MAXPARAGENS)
            {
                carreiras[i].paragens[carreiras[i].num_paragens] = n;
                carreiras[i].num_paragens++;
                num_ligacoes++;
            }
        }
    }
}

void adiciona_paragem_inicio_carreira(char *nome_carreira, char *nome_paragem)
{
    int i, k, n = devole_o_indice_da_paragem_pelo_nome(nome_paragem);

    for (i = 0; i < num_carreiras; i++)
    {
        if (strncmp(carreiras[i].nome, nome_carreira, MAXNOMECARREIRA - 1) == 0)
        {

            if (carreiras[i].num_paragens < MAXPARAGENS)
            {

                for (k = carreiras[i].num_paragens; k > 0; k--)
                    carreiras[i].paragens[k] = carreiras[i].paragens[k - 1];

                carreiras[i].paragens[0] = n;
                carreiras[i].num_paragens++;
                num_ligacoes++;
            }
        }
    }
}

/*esta funcao destina-se a ler o nome da carreira e das paragens do comando l*/
void getNomeLigacao(char *nome)
{ 
    int i = 0;
    char c = getchar();

    while (c == ' ')
        c = getchar();

    if (c == '"')
    {
        c = getchar();

        while (c != '"' && c != EOF && c != '\n' && i < MAXNOMEPARAGEM - 1)
        {
            nome[i++] = c;
            c = getchar();
        }
    }
    else
    {
        while (c != ' ' && c != EOF && c != '\n' && i < MAXNOMEPARAGEM - 1)
        {
            nome[i++] = c;
            c = getchar();
        }
    }

    nome[i] = '\0';
}

void adiciona_ligacoes(){
    Carreira *c = NULL;
    char nomeCarreira[MAXNOMECARREIRA], nomeParagemOrigem[MAXNOMEPARAGEM],
        nomeParagemDestino[MAXNOMEPARAGEM];
    float custo, duracao;
    if (num_ligacoes > MAXLIGACOES) return;
    getNomeLigacao(nomeCarreira);
    getNomeLigacao(nomeParagemOrigem);
    getNomeLigacao(nomeParagemDestino);
    scanf("%f", &custo);
    scanf("%f", &duracao);
    if (valida_carreira_existe(nomeCarreira) == FALSE) {
        printf("%s: no such line.\n", nomeCarreira);
        return;
    }
    c = encontra_carreira(nomeCarreira);

    if (valida_paragem_existe(nomeParagemOrigem) == FALSE) {
        printf("%s: no such stop.\n", nomeParagemOrigem);
        return;
    }
    if (valida_paragem_existe(nomeParagemDestino) == FALSE) {
        printf("%s: no such stop.\n", nomeParagemDestino);
        return;
    }

    if ((custo < 0) || (duracao < 0)) {
        printf("negative cost or duration.\n");
        return;
    }
    if (c->num_paragens > 1) {
        if ((strcmp(nomeParagemOrigem,
                    paragens[c->paragens[c->num_paragens - 1]].nome) != 0) &&
            ((strcmp(nomeParagemDestino, paragens[c->paragens[0]].nome) != 0))){
            printf("link cannot be associated with bus line.\n");
            return;
        }
    }

    if (c->num_paragens == 0) {
        adiciona_paragem_ao_fim_carreira(c->nome, nomeParagemOrigem);
        adiciona_paragem_ao_fim_carreira(c->nome, nomeParagemDestino);
        c->custo += custo;
        c->duracao += duracao;
        num_ligacoes--;
        return;
    }
    else if ((c->num_paragens > 1) && (strcmp(nomeParagemOrigem,
    paragens[c->paragens[c->num_paragens - 1]].nome) == 0) && 
    num_ligacoes < MAXLIGACOES)
    {
        adiciona_paragem_ao_fim_carreira(c->nome, nomeParagemDestino);

        c->custo += custo;
        c->duracao += duracao;
        return;
    }
    else if ((c->num_paragens > 1) && 
    (strcmp(nomeParagemDestino, paragens[c->paragens[0]].nome) == 0) && 
    num_ligacoes < MAXLIGACOES) {
        adiciona_paragem_inicio_carreira(c->nome, nomeParagemOrigem);
        c->custo += custo;
        c->duracao += duracao;
        return;
    }
}

/* algoritmo de ordenacao Bubble sort */
void bubble_sort(char arr[][MAXNOMECARREIRA], int n)
{
    int i, j;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (strcmp(arr[j], arr[j + 1]) > 0)
            {
                char temp[MAXNOMECARREIRA];
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}

/* Funcao da intersecao de carreiras----------------- */

void listar_intersecoes_carreiras()
{
    int carreiras_paragem[MAXPARAGENS][MAXCARREIRAS] = {0};
    int i, j, k;

    for (i = 0; i < num_carreiras; i++)
    {
        for (j = 0; j < carreiras[i].num_paragens; j++)
        {
            for (k = 0; k < num_paragens; k++)
            {
                if (carreiras[i].paragens[j] == k)
                {
                    carreiras_paragem[k][i] = 1;
                    break;
                }
            }
        }
    }

    for (i = 0; i < num_paragens; i++)
    {
        int num_carreiras_paragem = 0;
        int carreiras_paragem_ordem[MAXCARREIRAS] = {0};
        for (j = 0; j < num_carreiras; j++)
        {
            if (carreiras_paragem[i][j] == 1)
            {
                num_carreiras_paragem++;
                carreiras_paragem_ordem[j] = 1;
            }
        }
        if (num_carreiras_paragem > 1)
        {
            char carreiras_ordenadas[MAXCARREIRAS][MAXNOMECARREIRA];
            int num_carreiras_ordenadas = 0;
            printf("%s %d:", paragens[i].nome, num_carreiras_paragem);

            /* ordena as carreiras alfabeticamente */

            for (j = 0; j < num_carreiras; j++)
            {
                if (carreiras_paragem_ordem[j] == 1)
                {
                    strcpy(carreiras_ordenadas[num_carreiras_ordenadas],
                           carreiras[j].nome);
                    num_carreiras_ordenadas++;
                }
            }
            bubble_sort(carreiras_ordenadas, num_carreiras_ordenadas);

            for (j = 0; j < num_carreiras_ordenadas; j++)
            {
                printf(" %s", carreiras_ordenadas[j]);
            }
            printf("\n");
        }
    }
}

/* Funcao main--------------------------*/

int main()
{
    char c;

    /* as instrucoes a seguir sao relativas a linhA de comando */

    while ((c = getchar()) != EOF)
    {
        switch (c)
        {
        case 'q':
            return 0;
        case 'c':
            adiciona_e_lista_as_carreiras();
            break;
        case 'p':
            adiciona_e_lista_paragens();
            break;

        case 'l':
            adiciona_ligacoes();
            break;

        case 'i':
            listar_intersecoes_carreiras();
            break;
        }
    }

    return 0;
}
