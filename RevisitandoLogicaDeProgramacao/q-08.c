#include <stdio.h>
int main(){
    int i, n, fatorial;

    printf("Informe um numero:\n");
    scanf("%d", &n);

    if(n == 0 || n == 1){
        printf("Fatorial = 1");
    }else{
        fatorial = 1;
        for(i = 2; i <= n; i++){
            fatorial = fatorial * i;
        }
        printf("Fatorial = %d", fatorial);
    }
}