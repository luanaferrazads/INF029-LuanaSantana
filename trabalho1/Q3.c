/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
    int i;

    if(isCaseSensitive == 1){
        for(i = 0; texto[i] != '\0'; i++){
            if(texto[i] == c){
                qtdOcorrencias++;
            }
        }
    }else{
        char copia_do_texto[256];
        char copia_c;

        copia_c = c;

        for(i = 0; texto[i] != '\0'; i++){
            copia_do_texto[i] = texto[i];
        }
        copia_do_texto[i] = '\0';

        if(copia_c >= 'A' && copia_c <= 'Z'){
            copia_c += 32;
        }else{
            copia_c = copia_c;
        }

        for(i = 0; copia_do_texto[i] != '\0'; i++){
            if(copia_do_texto[i] >= 'A' && copia_do_texto[i] <= 'Z'){
                copia_do_texto[i] += 32;
            }else{
                copia_do_texto[i] = copia_do_texto[i];
            }
        }

        for(i = 0; copia_do_texto[i] != '\0'; i++){
            if(copia_do_texto[i] == copia_c){
                qtdOcorrencias++;
            }
        }

    }

    return qtdOcorrencias;
}
