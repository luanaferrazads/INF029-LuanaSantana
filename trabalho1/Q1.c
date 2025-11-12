#include "trabalho1.h"
#include <stdlib.h>
#include <stdio.h>

DataQuebrada quebraData(char data[]);
int bissexto(int ano);

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
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
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