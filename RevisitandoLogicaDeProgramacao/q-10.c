#include <stdio.h>
#include <string.h>
#define TAM 5

typedef struct ficha_pessoas{
    char nome[31];
    int idade;
    char cpf[16];
    char sexo;
} Pessoa;


int main(){
    Pessoa pessoas[TAM];
    int i;

    for(i = 0; i < TAM; i++){
        printf("Informe o nome:");
        fgets(pessoas[i].nome, 31, stdin);
        size_t ln = strlen(pessoas[i].nome) - 1;
        if(pessoas[i].nome[ln] == '\n'){
            pessoas[i].nome[ln] = '\0';
        }

        printf("Informe o sexo (F/M/O):");
        scanf("%c", &pessoas[i].sexo);

        printf("Informe a idade:");
        scanf("%d", &pessoas[i].idade);

        getchar();

        printf("Informe o CPF:");
        fgets(pessoas[i].cpf, 16, stdin);
        ln = strlen(pessoas[i].cpf) - 1;
        if(pessoas[i].cpf[ln] == '\n'){
            pessoas[i].cpf[ln] = '\0';
        }
    }

    printf("\n=== Lista de pessoas cadastradas ===\n");

    for(i =0; i < TAM; i++){
        printf("Nome: %s\n", pessoas[i].nome);
        printf("Sexo: %c\n", pessoas[i].sexo);
        printf("Idade: %d\n", pessoas[i].idade);
        printf("CPF: %s\n", pessoas[i].cpf);
    }

    return 0;
}
    