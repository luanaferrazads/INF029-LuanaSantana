#include "trabalho1.h"
#include <stdlib.h>
#include <stdio.h>

DataQuebrada quebraData(char data[]);
int bissexto(int ano);

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