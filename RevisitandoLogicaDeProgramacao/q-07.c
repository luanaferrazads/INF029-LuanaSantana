#include <stdio.h>
int main(){
    int numero, i, divisores;

    printf("Informe um número:\n");
    scanf("%d", &numero);


    for(i = 1; i <= numero; i++){
        if(numero % i == 0){
            divisores++;
        }
    }

    if(divisores == 2){
        printf("O número é primo");
    }else{
        printf("O número não é primo");
    }

  /*int ehPrimo = 1;
    for(int i = 2; i < numero; i++){
        if(numero % i == 0){
        ehPrimo = 0;
        break;     
        }
    }

    if(ehPrimo == 1){
        printf("O número é primo");
    }else{
        printf("O número não é primo");
    }*/

}