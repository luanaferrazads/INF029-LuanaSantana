#include <stdio.h>
int subtrai(int num1, int num2, int num3){
    return num1 - num2 - num3;
}

int main(){
    int n1, n2, n3;
    printf("Informe 3 números:\n");
    scanf("%d %d %d", &n1, &n2, &n3);

    printf("O resultado da subtração desses 3 números é: %d", subtrai(n1, n2, n3));
}