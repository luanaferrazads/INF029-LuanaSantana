// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Luana Roseli Rios Ferraz Santana
//  email: luanarrfs@hotmail.com
//  Matrícula: 20251160010
//  Semestre: 2025.2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>

int bissexto(int ano);
DataQuebrada quebraData(char data[]);
void removerAcentos(char *texto);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
    int datavalida = 1;
    DataQuebrada data_div = quebraData(data);

    if (!data_div.valido) datavalida = 0;

    int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(bissexto(data_div.iAno))
        dias_mes[1]++;

    if(data_div.iAno < 100)
        data_div.iAno += (data_div.iAno > 25)? 1900 : 2000;

    if(data_div.iAno < 1900 || data_div.iAno > 2025)
        datavalida = 0;
    if(data_div.iMes < 1 || data_div.iMes > 12)
        datavalida = 0;
    if(data_div.iDia < 1 || data_div.iDia > dias_mes[data_div.iMes - 1])
        datavalida = 0;

    return datavalida;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    
    DiasMesesAnos dma;
    int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dias_t = 0;
    DataQuebrada dataI = quebraData(datainicial);
    DataQuebrada dataF = quebraData(datafinal);


    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }else{
        if (dataI.iAno > dataF.iAno) {
            dma.retorno = 4;
            return dma;
        }
        if (dataI.iAno == dataF.iAno && dataI.iMes > dataF.iMes) {
            dma.retorno = 4;
            return dma;
        }
        if (dataI.iAno == dataF.iAno && dataI.iMes == dataF.iMes && dataI.iDia > dataF.iDia) {
            dma.retorno = 4;
            return dma;
        }

        dma.qtdAnos = dataF.iAno - dataI.iAno;
        if (dataI.iMes > dataF.iMes || (dataI.iMes == dataF.iMes && dataI.iDia > dataF.iDia))
            dma.qtdAnos--;
        dataI.iAno += dma.qtdAnos;

        dma.qtdMeses = 0;


        int m_i = (dataI.iMes >= dataF.iMes && dataI.iDia != dataF.iDia) ? dataI.iMes - 12 : dataI.iMes;
        int m_f = dataF.iMes;

        while (m_i < m_f) {
            dma.qtdMeses++;
            m_i++;
        }
        if (dataI.iDia > dataF.iDia) {
            dma.qtdMeses--;
        }
        if(dma.qtdMeses >= 12) {
            dma.qtdMeses -= 12;
            dma.qtdAnos++;
        }
        dataI.iMes += dma.qtdMeses;

        if (dataI.iMes > 12) {
            dataI.iMes -= 12;
            dataI.iAno++;
        }

        dias_mes[1] = (bissexto(dataF.iAno))? 29 : 28;
        dma.qtdDias = (dias_mes[dataI.iMes-1] - dataI.iDia) + dataF.iDia;
        dma.qtdDias += (bissexto(dataI.iAno) && !bissexto(dataF.iAno)) ? 1 : 0;
        dma.qtdDias -= (dma.qtdDias >= dias_mes[dataI.iMes - 1])? dias_mes[dataI.iMes - 1] : 0;


      dma.retorno = 1;
      return dma;
      
    }
    
}

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

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int i, j, k, tamBusca;

    removerAcentos(strTexto);
    removerAcentos(strBusca);

    for (tamBusca = 0; strBusca[tamBusca] != '\0'; tamBusca++);

    for (i = 0, k = 0; strTexto[i] != '\0'; i++) {

        for (j = 0; j < tamBusca; j++) {
            if (strTexto[i + j] != strBusca[j]) {
                break;
            }
        }

        if (j == tamBusca) {
            posicoes[k++] = i + 1;        
            posicoes[k++] = i + tamBusca; 
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}

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

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int ocorrencias = 0;
    int i, j;
    int vetBase[20], vetBusca[20];

    i = 0;
    while (numerobase > 0) {
        vetBase[i++] = numerobase % 10;
        numerobase /= 10;
    }
    int tamBase = i;

    i = 0;
    while (numerobusca > 0) {
        vetBusca[i++] = numerobusca % 10;
        numerobusca /= 10;
    }
    int tamBusca = i;

    for (i = 0; i < tamBase; i++) {

        for (j = 0; j < tamBusca; j++) {
            if (vetBase[i + j] != vetBusca[j])
                break;
        }

        if (j == tamBusca) {
            ocorrencias++;
            i += tamBusca - 1;   
        }
    }

    return ocorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[5])
 {

    int encontrado = 0;
    int lin, col, pos, tamP;
    char reverso[5];

    for (tamP = 0; palavra[tamP] != '\0'; tamP++);

    for (lin = tamP - 1, col = 0; lin >= 0; lin--, col++) {
        reverso[col] = palavra[lin];
    }

    for (lin = 0; lin < 8 && !encontrado; lin++) {
        for (col = 0; col <= 10 - tamP && !encontrado; col++) {

            for (pos = 0; pos < tamP; pos++) {
                if (matriz[lin][col + pos] != palavra[pos] &&
                    matriz[lin][col + pos] != reverso[pos]) {
                    break;
                }
            }

            if (pos == tamP)
                encontrado = 1;
        }
    }

    for (col = 0; col < 10 && !encontrado; col++) {
        for (lin = 0; lin <= 8 - tamP && !encontrado; lin++) {

            for (pos = 0; pos < tamP; pos++) {
                if (matriz[lin + pos][col] != palavra[pos] &&
                    matriz[lin + pos][col] != reverso[pos]) {
                    break;
                }
            }

            if (pos == tamP)
                encontrado = 1;
        }
    }

    for (lin = 0; lin <= 8 - tamP && !encontrado; lin++) {
        for (col = 0; col <= 10 - tamP && !encontrado; col++) {

            for (pos = 0; pos < tamP; pos++) {
                if (matriz[lin + pos][col + pos] != palavra[pos] &&
                    matriz[lin + pos][col + pos] != reverso[pos]) {
                    break;
                }
            }

            if (pos == tamP)
                encontrado = 1;
        }
    }

    for (lin = 0; lin <= 8 - tamP && !encontrado; lin++) {
        for (col = tamP - 1; col < 10 && !encontrado; col++) {

            for (pos = 0; pos < tamP; pos++) {
                if (matriz[lin + pos][col - pos] != palavra[pos] &&
                    matriz[lin + pos][col - pos] != reverso[pos]) {
                    break;
                }
            }

            if (pos == tamP)
                encontrado = 1;
        }
    }

    return encontrado;
}


int bissexto(int ano) {
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 4 == 0 && ano % 400 == 0)) {
        return 1;
    }
    return 0;
}


DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ 
		sDia[i] = '\0';  
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; 
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ 
		sMes[i] = '\0';  
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; 
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ 
		sAno[i] = '\0'; 
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}

void removerAcentos(char *texto) {
    int i = 0;
    while (texto[i] != '\0') {
        unsigned char uc = (unsigned char)texto[i];

        if (uc == 0xC3) {
            unsigned char next = (unsigned char)texto[i + 1];
            char substituto = 0;

            switch (next) {

                case 0xA1: case 0xA0: case 0xA2: case 0xA3:
                case 0x81: case 0x80: case 0x82: case 0x83:
                    substituto = 'a';
                    break;

                case 0xA9: case 0xA8: case 0xAA: case 0xAB:
                case 0x89: case 0x88: case 0x8A: case 0x8B:
                    substituto = 'e';
                    break;

                case 0xAD: case 0xAC: case 0xAE: case 0xAF:
                case 0x8D: case 0x8C: case 0x8E: case 0x8F:
                    substituto = 'i';
                    break;

                case 0xB3: case 0xB2: case 0xB4: case 0xB5: case 0xB6:
                case 0x93: case 0x92: case 0x94: case 0x95: case 0x96:
                    substituto = 'o';
                    break;

                case 0xBA: case 0xB9: case 0xBB: case 0xBC:
                case 0x9A: case 0x99: case 0x9B: case 0x9C:
                    substituto = 'u';
                    break;

                case 0xA7:
                case 0x87:
                    substituto = 'c';
                    break;

                default:
                    substituto = 0;
            }

            if (substituto) {
                texto[i] = substituto;

                int k = i + 1;
                while (texto[k + 1] != '\0') {
                    texto[k] = texto[k + 1];
                    k++;
                }
                texto[k] = '\0';
                i++;
                continue;
            }
        }

        if (texto[i] >= 'A' && texto[i] <= 'Z') {
            texto[i] = texto[i] + 32;
        }

        i++;
    }
}
