#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

typedef struct
{
    int *dados;
    int qtd;
    int tamanho;
} EstruturaAux;

EstruturaAux vetorPrincipal[TAM];

int posicaoValida(int posicao)
{
    return (posicao >= 1 && posicao <= TAM);
}

int existeEstrutura(int posicao)
{
    return vetorPrincipal[posicao].dados != NULL;
}

int temEspaco(EstruturaAux *p)
{
    return p->qtd < p->tamanho;
}

int buscarElemento(int posicao, int valor)
{
    for (int i = 0; i < vetorPrincipal[posicao].qtd; i++)
        if (vetorPrincipal[posicao].dados[i] == valor)
            return i;
    return -1;
}

int totalElementos(EstruturaAux *vet)
{
    int total = 0;
    for (int i = 0; i < TAM; i++)
        total += vet[i].qtd;
    return total;
}

void ordenarVetor(int vet[], int tamanho)
{
    for (int i = 1; i < tamanho; i++)
    {
        int aux = vet[i];
        int j = i - 1;
        while (j >= 0 && vet[j] > aux)
        {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = aux;
    }
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    if (!posicaoValida(posicao))
        return POSICAO_INVALIDA;

    posicao--;

    if (existeEstrutura(posicao))
        return JA_TEM_ESTRUTURA_AUXILIAR;

    if (tamanho < 1)
        return TAMANHO_INVALIDO;

    int *teste = malloc(tamanho * sizeof(int));
    if (!teste)
        return SEM_ESPACO_DE_MEMORIA;
    free(teste);

    vetorPrincipal[posicao].dados = malloc(tamanho * sizeof(int));
    vetorPrincipal[posicao].qtd = 0;
    vetorPrincipal[posicao].tamanho = tamanho;

    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    if (!posicaoValida(posicao))
        return POSICAO_INVALIDA;

    posicao--;

    if (!existeEstrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    if (!temEspaco(&vetorPrincipal[posicao]))
        return SEM_ESPACO;

    vetorPrincipal[posicao].dados[vetorPrincipal[posicao].qtd++] = valor;
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    if (!posicaoValida(posicao))
        return POSICAO_INVALIDA;

    posicao--;

    if (!existeEstrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    if (vetorPrincipal[posicao].qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    vetorPrincipal[posicao].qtd--;
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    if (!posicaoValida(posicao))
        return POSICAO_INVALIDA;

    posicao--;

    if (!existeEstrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    if (vetorPrincipal[posicao].qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    int idx = buscarElemento(posicao, valor);
    if (idx == -1)
        return NUMERO_INEXISTENTE;

    for (int i = idx; i < vetorPrincipal[posicao].qtd - 1; i++)
        vetorPrincipal[posicao].dados[i] = vetorPrincipal[posicao].dados[i + 1];

    vetorPrincipal[posicao].qtd--;
    return SUCESSO;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    return posicaoValida(posicao) ? SUCESSO : POSICAO_INVALIDA;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if (!posicaoValida(posicao))
        return POSICAO_INVALIDA;

    posicao--;

    if (!existeEstrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    for (int i = 0; i < vetorPrincipal[posicao].qtd; i++)
        vetorAux[i] = vetorPrincipal[posicao].dados[i];

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if (retorno != SUCESSO)
        return retorno;

    ordenarVetor(vetorAux, vetorPrincipal[posicao - 1].qtd);
    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int k = 0;
    for (int i = 0; i < TAM; i++)
        if (vetorPrincipal[i].dados)
            for (int j = 0; j < vetorPrincipal[i].qtd; j++)
                vetorAux[k++] = vetorPrincipal[i].dados[j];

    return (k == 0) ? TODAS_ESTRUTURAS_AUXILIARES_VAZIAS : SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);
    if (retorno != SUCESSO)
        return retorno;

    ordenarVetor(vetorAux, totalElementos(vetorPrincipal));
    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    if (!posicaoValida(posicao))
        return POSICAO_INVALIDA;

    posicao--;

    if (!existeEstrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    if (vetorPrincipal[posicao].tamanho + novoTamanho < 1)
        return NOVO_TAMANHO_INVALIDO;

    int novoTam = vetorPrincipal[posicao].tamanho + novoTamanho;
    int *novo = realloc(vetorPrincipal[posicao].dados, novoTam * sizeof(int));
    if (!novo)
        return SEM_ESPACO_DE_MEMORIA;

    vetorPrincipal[posicao].dados = novo;
    vetorPrincipal[posicao].tamanho = novoTam;

    if (vetorPrincipal[posicao].qtd > novoTam)
        vetorPrincipal[posicao].qtd = novoTam;

    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    if (!posicaoValida(posicao))
        return POSICAO_INVALIDA;

    posicao--;

    if (!existeEstrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    if (vetorPrincipal[posicao].qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    return vetorPrincipal[posicao].qtd;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    No *cabeca = criarNo(-1);
    No *atual = cabeca;

    for (int i = 0; i < TAM; i++)
        if (vetorPrincipal[i].dados)
            for (int j = 0; j < vetorPrincipal[i].qtd; j++)
            {
                atual->prox = criarNo(vetorPrincipal[i].dados[j]);
                atual = atual->prox;
            }

    if (!cabeca->prox)
    {
        free(cabeca);
        return NULL;
    }

    return cabeca;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    int i = 0;
    No *aux = inicio->prox;

    while (aux != NULL)
    {
        vetorAux[i++] = aux->conteudo;
        aux = aux->prox;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No *aux = *inicio;
    while (aux)
    {
        No *tmp = aux;
        aux = aux->prox;
        free(tmp);
    }
    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/
void inicializar()
{
    for (int i = 0; i < TAM; i++)
    {
        vetorPrincipal[i].dados = NULL;
        vetorPrincipal[i].qtd = 0;
        vetorPrincipal[i].tamanho = 0;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/
void finalizar()
{
    for (int i = 0; i < TAM; i++)
        if (vetorPrincipal[i].dados)
            free(vetorPrincipal[i].dados);
}
