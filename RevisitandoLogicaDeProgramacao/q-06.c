#include <stdio.h>
int main(){
    int idade;
    
    do{
        printf("Informe a sua idade:\n");
        scanf("%d", &idade);
        if(idade < 0){
           printf("Finalizando o programa..."); 
        }else if(idade >= 18){
            printf("É maior de idade!\n");
        }else{
            printf("É menor de idade!\n");
        }
    }while(idade >= 0);
}