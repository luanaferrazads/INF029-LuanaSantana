#include <stdio.h>
int main(){
    int idade1, idade2, soma;
    printf("Informe a primeira idade:\n");
    scanf("%d", &idade1);
    printf("Informe a segunda idade:\n");
    scanf("%d", &idade2);

    soma = idade1 + idade2;
    
    printf("A soma das idades %d e %d é: %d", idade1, idade2, soma);
    return 0;
}