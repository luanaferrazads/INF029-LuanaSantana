#include <stdio.h>

int fatorial(int num){
    if(num < 0 || num > 12){
        return -1;
    }else if(num == 0 || num == 1){
        return 1;
    }else{
        int fatorial = 1;
        for(int i = 2; i <= num; i++){
            fatorial = fatorial * i;
        }
        return fatorial;
    }
}

int main(){
    int numero;
    printf("Informe o número que você deseja encontrar o fatorial:\n");
    scanf("%d", &numero);

    int resultado = fatorial(numero); 
    if(resultado == -1){
        printf("Não é possível ser calculado o fatorial desse número!");
    }else{
        printf("O fatorial do numero %d é %d", numero, resultado);
    }
}

