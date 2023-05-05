/* iaed-23 - ist1103580 - project2 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#include "estruturas.h"

void inicializarSistema(Sistema *sistema) {
    sistema->listaParagens = NULL;
    sistema->tailListaParagens = NULL;
    sistema->listaCarreiras = NULL;
    sistema->tailListaCarreiras = NULL;
    sistema->listaLigacoes = NULL;
    sistema->tailListaLigacoes = NULL;
   
}

/* Funcao para ler espacos */

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

/* Funcao para ler nomes */

char *leNome()
{
    int i = 0;
    int c;
    char *s = malloc(sizeof(char));
    if (s == NULL)
    {
        printf("Erro ao alocar memoria\n");
        exit(1);
    }
    c = getchar();

   
    while (isspace(c))
    {
        c = getchar();
    }

    
    if (c == '"')
    {
        c = getchar();
        while (c != '"')
        {
            s[i] = c;
            i++;
            s = realloc(s, (i + 1) * sizeof(char));
            if (s == NULL)
            {
                printf("Erro ao alocar memoria\n");
                exit(1);
            }
            c = getchar();
        }
    }

    
    else
    {
        while (!isspace(c) && c != EOF)
        {
            s[i] = c;
            i++;
            s = realloc(s, (i + 1) * sizeof(char));
            if (s == NULL)
            {
                printf("Erro ao alocar memoria\n");
                exit(1);
            }
            c = getchar();
        }
        ungetc(c, stdin);
    }

    s[i] = '\0';
    return s;
}

/* Funcao para ler tudo que estiver ate ao final da linha */

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
