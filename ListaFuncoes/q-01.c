int soma(int num1, int num2){
    return num1 + num2;
}

int main(){
    int n1, n2;
    printf("Informe 2 números:\n");
    scanf("%d %d", &n1, &n2);

    printf("A soma dos 2 números informados é: %d", soma(n1, n2));
}