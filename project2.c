/* iaed-23 - ist1103580 - project2 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "project2.h"

/* Verifica se existe uma paragem com um determinado nome. */

Paragem *encontraParagem(Paragem *listaParagens, char *nome) {
    Paragem *p = listaParagens;
    while (p != NULL) {
        if (strcmp(p->nome, nome) == 0)
            return p;
        else
            p = p->next;
    }
    return NULL;
}

/* Cria uma nova paragem. */

void criaParagem(Sistema* s, char *nomeParagem, double latitude, double longitude) {
    
    Paragem *novaParagem = (Paragem *) malloc(sizeof(Paragem));
    novaParagem->latitude = latitude;
    novaParagem->longitude = longitude;
    novaParagem->numCarreiras = 0;
    novaParagem->nome = (char *)malloc(sizeof(char) * (strlen(nomeParagem) + 1));
    strcpy(novaParagem->nome, nomeParagem);
    novaParagem->carreiras = NULL;
    novaParagem->next = NULL;
    if (s->listaParagens == NULL) {
        novaParagem->prev = NULL;
        s->listaParagens = novaParagem;
        s->tailListaParagens = novaParagem;
    }
    else {
        novaParagem->prev = s->tailListaParagens;
        s->tailListaParagens->next = novaParagem;
        s->tailListaParagens = novaParagem;
    }
}

/* Mostra no output a paragem */

void mostraParagem(Paragem *paragem) {
    printf("%s: %16.12f %16.12f %d\n", paragem->nome, paragem->latitude,
           paragem->longitude, paragem->numCarreiras);
}

/* Mostra todas as paragens. */

void listaAsParagens(Paragem *listaParagens) {
    
    Paragem *paragem = listaParagens;
    while (paragem != NULL) {
        mostraParagem(paragem);
        paragem = paragem->next;
    }
}


/* Função para tratar o comando 'p'. */

void paragens(Sistema *sistema) {
    
    char *s = NULL;
    Paragem *p = NULL;
    int fimLinha = leEspacos();
    

    if (!fimLinha) {
        listaAsParagens(sistema->listaParagens);
        return;
    }
    s = leNome();
    fimLinha = leEspacos();
    if (!fimLinha) {
        if ((p = encontraParagem(sistema->listaParagens, s)) == NULL)
            printf("%s: no such stop.\n", s);
        else
            printf("%16.12f %16.12f\n", p->latitude, p->longitude);
    }
    else {
        double latitude, longitude;
        scanf("%lf%lf", &latitude, &longitude);
        if (encontraParagem(sistema->listaParagens, s) == NULL) {
            criaParagem(sistema, s, latitude, longitude);
            
           
        }
        else
            printf("%s: stop already exists.\n", s);
        /*leAteFinalLinha(_buffer);*/
    }
    /*free(s);*/
}

/* carreiras -----------------------------------------------------------------*/

/* Motra uma carreira */

void mostraCarreira(Carreira *c) {
    int numLigacoes = c->numLigacoes;

    printf("%s ", c->nome);
    if (numLigacoes > 0) {

        printf("%s %s ", c->ligacoes[0]->paragemOrigem->nome,
               c->ligacoes[numLigacoes - 1]->paragemDestino->nome);
        printf("%d ", numLigacoes + 1);
        printf("%.2f ", c->custoTotal);
        printf("%.2f\n", c->duracaoTotal);
    }
    else
        printf("%d %.2f %.2f\n", 0, 0.0, 0.0);
}

/* Mostra as ligações da carreira que a funcao recebe como argumento */

void mostraLigacoesCarreira(Carreira *c, int inverso) {

    Ligacao *ligacao = NULL;
    int numLigacoes = c->numLigacoes, i;

    if (numLigacoes == 0)
        return;
    if (inverso == FALSO) {
        for (i = 0; i < numLigacoes; i++) {
            ligacao = c->ligacoes[i];
            if (ligacao->paragemOrigem != NULL)
                printf("%s, ", ligacao->paragemOrigem->nome);
        }
        ligacao = c->ligacoes[numLigacoes - 1];
        printf("%s\n", ligacao->paragemDestino->nome);
    }
    else {
        for (i = numLigacoes - 1; i >= 0; i--) {
            ligacao = c->ligacoes[i];
            printf("%s, ", ligacao->paragemDestino->nome);
        }
        ligacao = c->ligacoes[0];
        printf("%s\n", ligacao->paragemOrigem->nome);
    }
}

/* Mostra todas as carreiras. */

void listaAsCarreiras(Carreira *listaCarreiras) {
    Carreira *c = listaCarreiras;
    while (c != NULL) {
        mostraCarreira(c);
        c = c->next;
    }
}

/* Encontra a carreira pelo nome e retorna um ponteiro para essa carreira */

Carreira *encontraCarreira(Carreira *listaCarreiras, char *nome) {
    Carreira *c = listaCarreiras;
    while (c != NULL) {
        if (strcmp(c->nome, nome) == 0)
            return c;
        else
            c = c->next;
    }
    return NULL;
}

/* Verifica se a paragem faz parte das ligacoes da carreira */

int encontraParagemCarreira(Carreira *c, Paragem *p) {
    int numLigacoes = c->numLigacoes;
    int i;
    Ligacao *ligacao = NULL;

    for (i = 0; i < numLigacoes; i++) {
        ligacao = c->ligacoes[i];
        if (ligacao->paragemOrigem == p)
            return i;
    }
    ligacao = c->ligacoes[numLigacoes - 1];
    if (ligacao->paragemDestino == p)
        return numLigacoes;
    return NAO_ENCONTRADO;
}

/* Cria uma carreira */

void criaCarreira(Sistema* s, char *nomeCarreira) {

    Carreira *novaCarreira = (Carreira *)malloc(sizeof(Carreira));
    if (novaCarreira == NULL) {
        printf("Erro ao criar nova carreira\n");
        return;
    }
    novaCarreira->custoTotal = 0.0;
    novaCarreira->duracaoTotal = 0.0;
    novaCarreira->numLigacoes = 0;
    novaCarreira->ligacoes = NULL;
    novaCarreira->nome = (char *)malloc(sizeof(char) * (strlen(nomeCarreira) + 1));
    strcpy(novaCarreira->nome, nomeCarreira);
    novaCarreira->next = NULL;
    if (s->listaCarreiras == NULL) {
        novaCarreira->prev = NULL;
        s->listaCarreiras = novaCarreira;
        s->tailListaCarreiras = novaCarreira;
    }
    else {
        novaCarreira->prev = s->tailListaCarreiras;
        (s->tailListaCarreiras)->next = novaCarreira;
        s->tailListaCarreiras = novaCarreira;
    }
}

/* Verifica se a string é um prefixo de tamanho pelo menos 3 da
   palavra inverso. */

int verificaInversoOk(char s[]) {
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

void carreiras(Sistema *sistema)
{

    char *s = NULL;
    char *_buffer = NULL;
    Carreira *c = NULL;
    int fimLinha = leEspacos();

    if (!fimLinha) {
        listaAsCarreiras(sistema->listaCarreiras);
        return;
    }
    s = leNome();
    c = encontraCarreira(sistema->listaCarreiras, s);

    fimLinha = leEspacos();
    if (!fimLinha) {
        if ((c = encontraCarreira(sistema->listaCarreiras, s)) == NULL) {

            criaCarreira(sistema, s);
        }
        else {

            mostraLigacoesCarreira(c, FALSO);
        }
    }
    else
    {
        _buffer = leNome();

        if (verificaInversoOk(_buffer)) {
            if (c == NULL) {
                printf("invalid bus line\n");
                /*free(s);*/
                if (_buffer != NULL)
                    /*free(_buffer);*/
                return;
            }
            mostraLigacoesCarreira(c, VERDADE);
        }
        else
            printf("incorrect sort option.\n");
        /* leAteFinalLinha(_buffer) ;*/
    }
    /*free(s);*/
}
/*Ligacao---------------------------------------------------------------------*/

/* Cria uma ligacao */

void criaLigacao(Ligacao **head, Ligacao **tail, Carreira *c,
                 Paragem *pOrigem, Paragem *pDestino, double custo, double duracao) {

    Ligacao *novaLigacao = (Ligacao *)malloc(sizeof(Ligacao));
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

/* Verifica se a ligacao existe e se sim devolve o ponteiro para esta */

Ligacao* encontraLigacao(Ligacao **head, Carreira *c, Paragem *pOrigem, 
                        Paragem *pDestino, double custo, double duracao) {
    Ligacao* l = NULL;
    
    l = *head;
    
    while(l != NULL) {
        
        if ((l->carreira == c) && (l->paragemOrigem == pOrigem) && 
        (l->paragemDestino == pDestino) && (l->custo == custo) && 
        (l->duracao == duracao)) {
            return l;
        }
        l = l->next;
    }
    return NULL;
}

/* Apaga a ligacao que recebe como argumento */

void apagaLigacao(Sistema* s, Ligacao* ligacao) {
    Ligacao* aux = ligacao; 
    
    if (aux != NULL) {
        if (aux->prev != NULL) {
            aux->prev->next = aux->next;
        }
        else {
            s->listaLigacoes = aux->next;
        }
        if (aux->next != NULL) {
            aux->next->prev = aux->prev;
        }
        else {
            s->tailListaLigacoes = aux->prev;
        }
        
    /*
    free(aux);
    aux = NULL;*/
    }
    
}
/* Acrescenta uma nova ligação no fim de uma carreira. */

void acrescentaLigacaoFim(Carreira *carreira, Ligacao *ligacao) {
    if (carreira->ligacoes == NULL) {
        carreira->ligacoes = (Ligacao **)malloc(sizeof(ligacao));
        carreira->ligacoes[0] = ligacao;
    }

    else {
        int numLigacoes = carreira->numLigacoes;
        carreira->ligacoes = (Ligacao **)realloc(carreira->ligacoes, (numLigacoes + 1) * sizeof(Ligacao));
        carreira->ligacoes[numLigacoes] = ligacao;
    }
    carreira->custoTotal += ligacao->custo;
    carreira->duracaoTotal += ligacao->duracao;
    carreira->numLigacoes++;
}
/* Acrescenta uma nova ligação no início de uma carreira. */

void acrescentaLigacaoInicio(Carreira *carreira, Ligacao *ligacao) {
    int i;

    if (carreira->ligacoes == NULL) {
        carreira->ligacoes = (Ligacao **)malloc(sizeof(Ligacao));
        carreira->ligacoes[0] = ligacao;
    }
    else {
        int numLigacoes = carreira->numLigacoes;
        carreira->ligacoes = (Ligacao **)realloc(carreira->ligacoes, (numLigacoes + 1) * sizeof(Ligacao));
        for (i = numLigacoes; i > 0; i--) {
            carreira->ligacoes[i] = carreira->ligacoes[i - 1];
        }
        carreira->ligacoes[0] = ligacao;
    }
    carreira->custoTotal += ligacao->custo;
    carreira->duracaoTotal += ligacao->duracao;
    carreira->numLigacoes++;
}

/* Adiciona que existe uma nova carreira associada a uma paragem. */

void adicionaCarreiraParagem(Paragem *paragem, Carreira *carreira) {
    int i;
    for (i = 0; i < paragem->numCarreiras; i++) {
        if (strcmp(paragem->carreiras[i]->nome, carreira->nome) == 0) {
            return;
        }
    }
    paragem->carreiras = (Carreira **)realloc(paragem->carreiras, (paragem->numCarreiras + 1) * sizeof(Carreira));
    paragem->carreiras[paragem->numCarreiras] = carreira;
    paragem->numCarreiras++;
}

/* Adiciona primeira ligacao da carreira. */

void adicionaPrimeiraLigacao(Ligacao **head, Ligacao **tail, Carreira *c,
            Paragem *pOrigem, Paragem *pDestino, double custo, double duracao) {

    adicionaCarreiraParagem(pOrigem, c);
    if (pOrigem != pDestino)
        adicionaCarreiraParagem(pDestino, c);
    criaLigacao(head, tail, c, pOrigem, pDestino, custo, duracao);
    acrescentaLigacaoFim(c, *tail);
}

/* Adiciona uma nova ligação a uma carreira. */

void adicionaLigacao(Sistema* s, Carreira *c, Paragem *pOrigem, Paragem *pDestion,
                     double custo, double duracao) {
    int numLigacoesCarreira = c->numLigacoes;

    if (numLigacoesCarreira == 0)
        adicionaPrimeiraLigacao(&s->listaLigacoes, &s->tailListaLigacoes, c, 
                                pOrigem, pDestion, custo, duracao);
    else {
        Ligacao *primeiraLigacao = *c->ligacoes;
        Ligacao *ultimaLigacao = c->ligacoes[numLigacoesCarreira - 1];
        if (pOrigem == ultimaLigacao->paragemDestino) {
            if (encontraParagemCarreira(c, pDestion) == NAO_ENCONTRADO)
                adicionaCarreiraParagem(pDestion, c);
            criaLigacao(&s->listaLigacoes, &s->tailListaLigacoes, c, pOrigem, 
                        pDestion, custo, duracao);
            acrescentaLigacaoFim(c, s->tailListaLigacoes);
        }
        else if (pDestion == primeiraLigacao->paragemOrigem) {
            if (encontraParagemCarreira(c, pOrigem) == NAO_ENCONTRADO)
                adicionaCarreiraParagem(pOrigem, c);
            criaLigacao(&s->listaLigacoes, &s->tailListaLigacoes, c, pOrigem, 
                        pDestion, custo, duracao);
            acrescentaLigacaoInicio(c, s->tailListaLigacoes);
        }
        else
            printf("link cannot be associated with bus line.\n");
    }
}

/* Função para tratar o comando 'l'. */

void ligacoes(Sistema* s) {

    char *nomeCarreira = NULL;
    char *nomeOrigem = NULL;
    char *nomeDestino = NULL;
    double custo, duracao;
    Carreira *carreira;
    Paragem *pOrigem;
    Paragem *pDestino;

    leEspacos();
    nomeCarreira = leNome();
    leEspacos();
    nomeOrigem = leNome();
    leEspacos();
    nomeDestino = leNome();

    scanf("%lf%lf", &custo, &duracao);

    /*leAteFinalLinha(_buffer);*/

    carreira = encontraCarreira(s->listaCarreiras, nomeCarreira);
    if (carreira == NULL) {

        printf("%s: no such line.\n", nomeCarreira);
    }
    else {

        pOrigem = encontraParagem(s->listaParagens, nomeOrigem);
        if (pOrigem == NULL)
            printf("%s: no such stop.\n", nomeOrigem);
        else {
            pDestino = encontraParagem(s->listaParagens, nomeDestino);
            if (pDestino == NULL)
                printf("%s: no such stop.\n", nomeDestino);
            else if (custo < 0.0 || duracao < 0.0)
                printf("negative cost or duration.\n");
            else
                adicionaLigacao(s, carreira, pOrigem, pDestino, custo, duracao);
        }
    }
    /*free(nomeCarreira);
    free(nomeOrigem);
    free(nomeDestino);*/
}

/* Aplica Bubble Sort a um vector de carreiras. */

void ordenaCarreiras(Carreira **carreiras, int numCarreiras) {
    int i, j, houveTroca = VERDADE;
    for (i = 0; houveTroca && i < numCarreiras - 1; i++) {
        houveTroca = FALSO;
        for (j = 0; j < numCarreiras - 1 - i; j++) {
            if (strcmp(carreiras[j]->nome, carreiras[j + 1]->nome) > 0) {
                Carreira *aux = carreiras[j];
                carreiras[j] = carreiras[j + 1];
                carreiras[j + 1] = aux;
                houveTroca = VERDADE;
            }
        }
    }
}

/* Função para tratar o comando 'i'. */

void intersecoes(Sistema* s) {
    
    Paragem *p = s->listaParagens;
    int c, numCarreiras;
    Carreira **carreiras;

    while (p != NULL) {
        numCarreiras = p->numCarreiras;
        if (numCarreiras > 1) {
            printf("%s %d:", p->nome, numCarreiras);
            carreiras = p->carreiras;
            ordenaCarreiras(carreiras, numCarreiras);
            for (c = 0; c < numCarreiras; c++) {
                printf(" %s", carreiras[c]->nome);
            }
            printf("\n");
        }
        p = p->next;
    }
}


/*comando 'r' ----------------------------------------------------------------*/

/* Remove a carreira do vetor de carreiras que a paragem esta associada */

void removeCarreiraParagens(Carreira *carreira, Paragem *paragens) {
    while (paragens != NULL) {
        int i, j, numCarreiras = paragens->numCarreiras;
        for (i = 0; i < numCarreiras; i++) {
            if (paragens->carreiras[i] == carreira) {
                for (j = i; j < numCarreiras - 1; j++) {
                    paragens->carreiras[j] = paragens->carreiras[j + 1];
                }
                paragens->numCarreiras--;
            }
        }
        paragens = paragens->next;
    }
}

/* Apaga as ligacoes que tem a carreira associada */

void removeLigacoesComCarreira(Ligacao **ligacoes, Ligacao ** tailLigacoes, Carreira *carreira) {
    
    Ligacao *l = *ligacoes;
    while (l != NULL) {
        
        if (l->carreira == carreira) {
            
            if (l->prev != NULL) {
                
                l->prev->next = l->next;
            }
            else {
                
                *ligacoes = l->next;
            }
            if (l->next != NULL) {
                
                l->next->prev = l->prev;
            }
            else {
                
                *tailLigacoes = l->prev;
            }
            
        }
        l = l->next;
    }
    
   /*free(l);*/
}
/* Funcao que trata do comando 'r. */
void apagaCarreira(Sistema* s)
{
    
    char *nome = NULL;
    Carreira *aux = NULL;
    leEspacos();
    nome = leNome();
    aux = encontraCarreira(s->listaCarreiras, nome);
    if (aux != NULL)
    {
        if (aux->prev != NULL) {
            aux->prev->next = aux->next;
        }
        else {
            s->listaCarreiras = aux->next;
        }
        if (aux->next != NULL) {
            aux->next->prev = aux->prev;
        }
        else {
            s->tailListaCarreiras = aux->prev;
        }
        removeLigacoesComCarreira(&s->listaLigacoes, &s->tailListaLigacoes, aux);
        removeCarreiraParagens(aux, s->listaParagens);
        /*free(aux);*/
    }
    else
        printf("%s: no such line.\n", nome);
    
    /*free(nome);*/
}

/*comando 'e' ----------------------------------------------------------------*/
   
/* Altera as ligacoes de uma carreira apos a paragem ser eliminada */

void eliminaLigacaoCarreira(Sistema* s, Paragem* p) {
    Carreira *c = s->listaCarreiras;
    int i, j;
    while (c != NULL)
    {
        int numLigacoes = c->numLigacoes;
        i = 0;

        while (i < numLigacoes) {   
            /*apagar a primeira ligação*/
            if ((strcmp(c->ligacoes[i]->paragemOrigem->nome, p->nome) == 0) && (i==0)) {
                
                
                
                c->custoTotal-= c->ligacoes[i]->custo;
                c->duracaoTotal-= c->ligacoes[i]->duracao;
                
                c->ligacoes[i] = NULL;
                
                for (j = 1; j < numLigacoes; j++) {
                    c->ligacoes[j - 1] = c->ligacoes[j];
                }
                c->ligacoes[numLigacoes - 1] = NULL;
                c->numLigacoes--;
                numLigacoes--;
                
            } 
            /*criar uma nova ligação e apagar as duas antigas*/
            else if ((strcmp(c->ligacoes[i]->paragemDestino->nome, p->nome) == 0) && ((i + 1) != numLigacoes)) {
                
               
                Ligacao *novaLigacao = NULL;
                
                double newCusto = (c->ligacoes[i]->custo + c->ligacoes[i+1]->custo);
                double newDuracao = (c->ligacoes[i]->duracao + c->ligacoes[i+1]->duracao);
                
                criaLigacao(&s->listaLigacoes, &s->tailListaLigacoes, c,
                c->ligacoes[i]->paragemOrigem, c->ligacoes[i + 1]->paragemDestino, newCusto, newDuracao);
                
                novaLigacao = encontraLigacao(&s->listaLigacoes, c, c->ligacoes[i]->paragemOrigem, 
                c->ligacoes[i + 1]->paragemDestino, newCusto, newDuracao);
                
                c->ligacoes[i] = NULL;
                c->ligacoes[i + 1] = NULL;
                c->ligacoes[i] = novaLigacao;
                for (j = i + 2; j < numLigacoes; j++) {
                    c->ligacoes[j - 1] = c->ligacoes[j];
                }
                c->ligacoes[numLigacoes - 1] = NULL;

                c->numLigacoes -= 1;
                
                numLigacoes -= 1;
                /*if ((c->ligacoes = realloc(c->ligacoes, numLigacoes)) == NULL)
                    printf("erro ao realocar memoria\n");
                */

            }
            /*apagar a última ligação*/
            else if ((strcmp(c->ligacoes[i]->paragemDestino->nome, p->nome) == 0) && ((i + 1) == numLigacoes)) {
                
                c->custoTotal-= c->ligacoes[i]->custo;
                c->duracaoTotal-= c->ligacoes[i]->duracao;
                
                c->ligacoes[i] = NULL;
                c->numLigacoes--;
                numLigacoes--;
               
            }
            else {
                
                i++;
            }   
        }
        
        c = c->next;
        
    }
}

/* Funcao para tratar do comando 'e'.*/

void apagaParagem(Sistema* s) {
    char *nome = NULL;
    Paragem *aux = NULL;
    leEspacos();
    nome = leNome();
    aux = encontraParagem(s->listaParagens, nome);

    if (aux != NULL) {
        eliminaLigacaoCarreira(s, aux);
        if (aux->prev != NULL)
        {
            aux->prev->next = aux->next;
        }
        else
        {
            s->listaParagens = aux->next;
        }
        if (aux->next != NULL)
        {
            aux->next->prev = aux->prev;
        }
        else {
            s->tailListaParagens = aux->prev;
        }

        /*free(aux);*/
    }
    else
        printf("%s: no such stop.\n", nome);
   /*free(nome);*/
}

/*Comando 'a' ----------------------------------------------------------------*/

/* Apaga as paragens todas do sistema*/

void apagaParagens(Sistema* sistema)
{
    Paragem *p = NULL;
    p = sistema->listaParagens;
    while (p != NULL) {
        sistema->listaParagens = p->next;
        if (p->nome) {
            free(p->nome);
            p->nome = NULL;
        }
        
        if (p!= NULL) {
            free(p);
            p = NULL;
        }
        p = sistema->listaParagens;
    }
}

/* Apaga as carreiras todas do sistema*/

void apagaCarreiras(Sistema* sistema) {
    Carreira *c = NULL;
    c = sistema->listaCarreiras;
    while (c != NULL) {
        sistema->listaCarreiras = c->next;
        /*if (c->nome != NULL) {
            free(c->nome);
            c->nome = NULL;
        }
        if (c->ligacoes) {
            free(c->ligacoes);
            c->ligacoes = NULL;
        }
        if (c != NULL) {
            free(c);
            c = NULL;
        }*/
        c = sistema->listaCarreiras;
    }

}

/* Apaga as ligacoes todas do sistema*/

void apagaLigacoes(Sistema* sistema) {
    Ligacao* l = NULL;
    l = sistema->listaLigacoes;
    while (l != NULL) {
        sistema->listaLigacoes = l->next;
        
        /*free(l);*/
        l = sistema->listaLigacoes;
    }

}

/* Funcao para tratar do coando 'a'*/

void apagaSistema(Sistema* sistema) {
    apagaParagens(sistema);
    apagaCarreiras(sistema);
    apagaLigacoes(sistema);

}
