#include <stdio.h>
#define MAX 10
int main(){
    int numeros[MAX];
    int primos[MAX];
    int i, j;
    int soma = 0;
    //inicializar vetor primos
    for(i = 0; i < MAX; i++){
       primos[i] = 1;
    }
    //inicializar vetor números
    for(i = 0; i < MAX; i++){
        printf("Informe o %d° número:  ", i+1);
        scanf("%d", &numeros[i]);
    }
    //Confere se o numero não é primo (primos[i] = 0)
    for(i = 0; i < MAX; i++){
        for(j = 2; j < numeros[i]; j++){
            if(numeros[i] % j == 0){
                primos[i] = 0;
                break;
            }
        }
    }    
    
    printf("São números primos: [");
    for(i = 0; i < MAX; i++){
        if(primos[i] == 1){
            soma += numeros[i];
            printf("%d ", numeros[i]);
        }
    }
    printf("]\n");
    printf("A soma de todos os números primos é: %d", soma);
    
}