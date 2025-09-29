#include <stdio.h>
int main(){
    int idade;
    printf("Informe a sua idade:\n");
    scanf("%d", &idade);

    if(idade >= 18){
        printf("É maior de idade!");
    }else{
        printf("É menor de idade!");
    }
}
    
