#include <stdio.h>
#include <string.h>
#include "conio.h"

#define SIZE 200

char nome [SIZE] [50];
char email [SIZE] [50];
char data_nasc[10];
char cpf[11] ;
int op;
void cadastro ();
int valido;

/* Estrutura para salvar as informações do cadastro*/
struct pessoa{
	char nome [SIZE];
	char email [SIZE];
	char cpf[11]; //funciona como identificador unico da pessoa
};

//prototipo de funcoes
void ler_cpf();
int conversor(char valor);
int validarCPF();
void ler_data();

int main () {
	cadastro();
}

void cadastro () {
	static int linha, opt;
	char car;
	do{
		printf ("\n Digite o nome: ");
		scanf ("%s", &nome[linha]);
		//leitura da data
		ler_data();
		printf ("\n Digite o email: ");
		scanf ("%s", &email[linha]);
		//leitura do cpf
		do{
			ler_cpf();
			opt = validarCPF();
			if(opt != 1){
				printf("\nDigite 's' para continuar e 'n' para cancelar?\n");
				car = getche();
				if(car == 'n' || car == 'N'){
					opt = 1;
				}				
			}			
		}while(opt != 1);
		
		printf ("\n Digite 1 para continuar ou outro valor para sair\n");
		scanf ("%d", &op);
		linha++;
		if(op != 1)
			printf("\n\n\n\n Bye bye! =D \n\n\n\n");

	}while(op == 1);

}

/*
 * Função le o cpf e coloca pontos e hífen automaticamente
 * 
 * Primeira versão
 * Próxima versão avisará a falta de dígitos e etc...
 */
 void ler_cpf(){
 	int cont = 0, cont1 =0;
 	char ch;
 	int saida = 0;

 	printf("\n Digite o CPF: ");
 	do{
 		fflush(stdin); // limpeza de buffer windows 
		__fpurge(stdin); // limpeza de buffer Linux
		ch = getche(); 		//le um caracter e o exibe na tela automaticamente - não necessita de enter
		cpf[cont1] = ch;
		cont1++;		//contador o veetor cpf
		cont++;			//contador de dígitos
		fflush(stdin); // limpeza de buffer windows 
		__fpurge(stdin); // limpeza de buffer Linux

		//coloca os pontos e o hífen
		if (cont == 3 || cont == 6 ){
			printf(".");
		}
		if(cont == 9){
			printf("-");
		}
	}while(cont < 11);
	//printf("\nCPF: %s\n", &cpf);
	printf("\n\n");
}

/*função responsável por converter um caractere compreendido no intervalo de 0 a 9 em inteiro (no mesmo intervalo)*/
int conversor(char valor){
	switch(valor){
		case '9': return 9;
		case '8': return 8;
		case '7': return 7;
		case '6': return 6;
		case '5': return 5;
		case '4': return 4;
		case '3': return 3;
		case '2': return 2;
		case '1': return 1;
		case '0': return 0;
	}
}

int validarCPF(){
	int numero[11], dig1,dig2,soma=0,valor,i;

// convertendo caracteres em int
	for(i=0;i<11;i++){
		numero[i]=conversor(cpf[i]);
        //	printf("%d\n", numero[i]);
	}

// calculando primeiro dígito
	for(i = 0; i < 9; i++)
		soma+= numero[i]*(10-i);
	valor=soma%11;
	if(valor == 0 || valor == 1)
		dig1 = 0;
	else
		dig1 = 11 - valor;
	numero[9] = dig1;

// calculando segundo dígito
	soma = 0;
	for(i = 0; i < 10; i++)
		soma+= numero[i]*(11-i);
	valor = soma%11;
	if(valor == 0 || valor == 1)
		dig2 = 0;
	else
		dig2 = 11-valor;

// exibindo resultado
	if(dig1 == numero[9] && dig2 == numero[10]){
		printf("\nCPF correto: ");
		for(i = 0;i < 11; i++){
			if(i == 3 || i == 6){
				printf(".");
			}
			if(i == 9){
				printf("-");
			}
			printf("%d",numero[i]);
		}
		return 1;
	}
	else{
		printf("\nProblemas nos digitos verificadores!");
		printf("\n\nDigitos verificadores esperados para esta sequencia: %d%d",dig1,dig2);
	}
	//printf("\n\n\n");
	return 0;
}

/* função de leitura de data */
void ler_data(){
	char data[8], ch;
	int cont = 0, i, j;

	printf("\nDigite a data de nascimento no formato dd/mm/aaaa\n");
	data[2] = data[4] = '/';
	for (i = 0; i < 8; i++){
		fflush(stdin); // limpeza de buffer windows 
		__fpurge(stdin); // limpeza de buffer Linux
		
		ch = getche();
		data[i] = ch;

		if(i == 1 || i == 3){
			printf("/");
		}	
		if(i == 7){
			data[8] = '\0';
		}	
	}
	printf("\n data = %s\n", &data);

	for (i = 0, j = 0; i < 11 ; i++, j++){
		if( j == 10){
			data_nasc[j] = '\0';
			break;
		}
		if(i == 2 || i == 4){
			data_nasc[j] = '/';
			data_nasc[j+1] = data[i];
			j++;
		}else{
			data_nasc[j] = data[i];	
		}
		
	}
	printf("\n data2 = %s\n", &data_nasc );
}