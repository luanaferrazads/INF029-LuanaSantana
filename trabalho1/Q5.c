/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    int resto;
    int inverso = 0;
    
    for(int i = 0; num != 0; i++){
        resto = num % 10;
        inverso = inverso * 10 + resto;
        num /= 10;
    }
    
    num = inverso;

    return num;
}
