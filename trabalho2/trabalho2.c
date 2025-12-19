#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

typedef struct
{
    int *dados;
    int quantidade;
    int capacidade;
} Ponto;

Ponto vetorPrincipal[TAM];

int valida_posicao(int pos)
{
    return (pos >= 1 && pos <= TAM) ? 1 : 0;
}

int tem_estrutura(int pos)
{
    return vetorPrincipal[pos].dados != NULL;
}

int estrutura_vaga(Ponto *p)
{
    return p->quantidade < p->capacidade;
}

int BuscaValor(int posicao, int valor)
{
    for (int i = 0; i < vetorPrincipal[posicao].quantidade; i++)
    {
        if (vetorPrincipal[posicao].dados[i] == valor)
            return i;
    }
    return -1;
}

int get_qtd(Ponto *vet)
{
    int total = 0;
    for (int i = 0; i < TAM; i++)
        total += vet[i].quantidade;
    return total;
}

void ordena_vetor(int vet[], int tam)
{
    for (int i = 1; i < tam; i++)
    {
        int temp = vet[i];
        int j = i - 1;
        while (j >= 0 && vet[j] > temp)
        {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = temp;
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
    posicao--;
    if (!valida_posicao(posicao + 1))
        return POSICAO_INVALIDA;
    if (tem_estrutura(posicao))
        return JA_TEM_ESTRUTURA_AUXILIAR;
    if (tamanho < 1)
        return TAMANHO_INVALIDO;

    int *teste = malloc(tamanho * sizeof(int));
    if (!teste)
        return SEM_ESPACO_DE_MEMORIA;
    free(teste);

    vetorPrincipal[posicao].dados = malloc(tamanho * sizeof(int));
    vetorPrincipal[posicao].quantidade = 0;
    vetorPrincipal[posicao].capacidade = tamanho;

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
    if (!valida_posicao(posicao))
        return POSICAO_INVALIDA;

    posicao--;
    if (!tem_estrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    if (!estrutura_vaga(&vetorPrincipal[posicao]))
        return SEM_ESPACO;

    vetorPrincipal[posicao].dados[vetorPrincipal[posicao].quantidade++] = valor;
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
    posicao--;
    if (!valida_posicao(posicao + 1))
        return POSICAO_INVALIDA;
    if (!tem_estrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao].quantidade == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    vetorPrincipal[posicao].quantidade--;
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
    posicao--;
    if (!valida_posicao(posicao + 1))
        return POSICAO_INVALIDA;
    if (!tem_estrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao].quantidade == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    int idx = BuscaValor(posicao, valor);
    if (idx < 0)
        return NUMERO_INEXISTENTE;

    for (int i = idx; i < vetorPrincipal[posicao].quantidade - 1; i++)
        vetorPrincipal[posicao].dados[i] = vetorPrincipal[posicao].dados[i + 1];

    vetorPrincipal[posicao].quantidade--;
    return SUCESSO;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    return (posicao >= 1 && posicao <= 10) ? SUCESSO : POSICAO_INVALIDA;
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
    posicao--;
    if (!valida_posicao(posicao + 1))
        return POSICAO_INVALIDA;
    if (!tem_estrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    for (int i = 0; i < vetorPrincipal[posicao].quantidade; i++)
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
    if (retorno == SUCESSO)
        ordena_vetor(vetorAux, vetorPrincipal[posicao - 1].quantidade);
    return retorno;
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
    {
        if (tem_estrutura(i) && vetorPrincipal[i].quantidade > 0)
        {
            for (int j = 0; j < vetorPrincipal[i].quantidade; j++)
                vetorAux[k++] = vetorPrincipal[i].dados[j];
        }
    }
    return (k > 0) ? SUCESSO : TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
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
    ordena_vetor(vetorAux, get_qtd(vetorPrincipal));
    return retorno;
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
    posicao--;
    if (!valida_posicao(posicao + 1))
        return POSICAO_INVALIDA;
    if (!tem_estrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao].capacidade + novoTamanho <= 0)
        return NOVO_TAMANHO_INVALIDO;

    int *tmp = realloc(vetorPrincipal[posicao].dados, (vetorPrincipal[posicao].capacidade + novoTamanho) * sizeof(int));
    if (!tmp)
        return SEM_ESPACO_DE_MEMORIA;

    vetorPrincipal[posicao].dados = tmp;
    vetorPrincipal[posicao].capacidade += novoTamanho;
    if (vetorPrincipal[posicao].quantidade > vetorPrincipal[posicao].capacidade)
        vetorPrincipal[posicao].quantidade = vetorPrincipal[posicao].capacidade;

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
    posicao--;
    if (!valida_posicao(posicao + 1))
        return POSICAO_INVALIDA;
    if (!tem_estrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao].quantidade == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;
    return vetorPrincipal[posicao].quantidade;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
void Inserir(No *inicio, int valor)
{
    No *novo = (No *)malloc(sizeof(No));
    novo->conteudo = valor;
    novo->prox = NULL;

    No *aux = inicio;
    while (aux->prox)
        aux = aux->prox;

    aux->prox = novo;
}

No *montarListaEncadeadaComCabecote()
{
    No *inicioLista = (No *)malloc(sizeof(No));
    inicioLista->prox = NULL;

    int tamanho = get_qtd(vetorPrincipal);
    if (tamanho == 0)
        return NULL;

    int *todos = malloc(tamanho * sizeof(int));
    getDadosDeTodasEstruturasAuxiliares(todos);
    for (int i = 0; i < tamanho; i++)
        Inserir(inicioLista, todos[i]);

    free(todos);
    return inicioLista;
}

/*
Objetivo: retorna os números da lista encadeada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    No *aux = inicio->prox;
    int i = 0;
    while (aux)
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
    No *atual = *inicio;
    while (atual)
    {
        No *prox = atual->prox;
        free(atual);
        atual = prox;
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
        vetorPrincipal[i].quantidade = 0;
        vetorPrincipal[i].capacidade = 0;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.
*/
void finalizar()
{
    for (int i = 0; i < TAM; i++)
    {
        if (vetorPrincipal[i].dados)
        {
            free(vetorPrincipal[i].dados);
            vetorPrincipal[i].dados = NULL;
            vetorPrincipal[i].quantidade = 0;
            vetorPrincipal[i].capacidade = 0;
        }
    }
}
