#include <stdio.h>
int main(){
    int a, b;
    printf("Informe o primeiro numero:\n");
    scanf("%d", &a);
    printf("Informe o segundo numero:\n");
    scanf("%d", &b);
 
    a = a + b;
    b = a - b;
    a = a - b;
    
    printf("O valor de a é: %d e o valor de b é: %d", a, b);
}