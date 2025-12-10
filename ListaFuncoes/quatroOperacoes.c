#include <stdio.h>

typedef struct{
    int soma;
    int subtracao;
    int multiplicacao;
    int divisao;
} Resultados;

Resultados quatro_operacoes(int num1, int num2){
    Resultados op;
    op.soma = num1 + num2;
    op.subtracao = num1 -num2;
    op.multiplicacao = num1 * num2;
    op.divisao = num1 / num2;

    return op;
}

int main(){
    int a = 10;
    int b = 5;

    Resultados r = quatro_operacoes(a,b);

    printf("Soma: %d\n", r.soma);
    printf("Subtracao: %d\n", r.subtracao);
    printf("multiplicacao: %d\n", r.multiplicacao);
    printf("divisao: %d", r.divisao);
}