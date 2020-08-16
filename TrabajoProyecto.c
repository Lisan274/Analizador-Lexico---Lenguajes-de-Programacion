/*
Grupo #4
Lisandro Alfredo Suarez Salinas - 20161002968
Daniel José Chavarría - 20141005789
Eber Josue Dominguez - 20141004595
Yoselin Dayriela Montes - 20121012555
Yolani Marieli Madrid - 20131004973

Descripcion: El siguiente proyecto esta basado en la creacion de un analizador lexico, tomando en cuenta el funcionamiento de este
busca que atraves del lenguaje C descomponer una entrada de texto y analizarla en busqueda de palabras reservadas, tipos de datos, y 
demas elementos de un lenguaje de programacion, Se uso el compilador minGW 6.3.0, ademas del uso del IDE Zinjai y de editores de texto
como Code y Sublime.
*/


#include <ctype.h>//Sirve para isdigit y isalpha
#include <stdlib.h>//Sirve para el system(pause)
#include <stdbool.h>//SIRVE PARA LOS bool
#include <stdio.h>//Es la libreria de FILE
#include <string.h>//Sirve para strcpy


//using namespace std;
void buscarRESERVADOSID();
const char *pal_reser[]={"inicio","sino","entrada_datos","fin","cambiar","descanso","ciclo","retornar","funcionMain","nombre","hacer mientras","para","mientras","donde", "para","si","entero", "caracter","retorno", "decimal", "imprimir","fin",};//arreglo que contiene todas las palabras reservadas permitidas
int tamIndicador=sizeof(pal_reser)/sizeof(char *);
char identificador[100];

int main(){
	
	FILE *file;
	char *fichero = "codigo.txt"; //declarar la direcci�n o nombre del archivo a leer
	char c; // char que contendr� cada caracter le�do del archivo
	char estado = 'A'; //Bandera para indicar el estado en el que se encuentra nuestro automata programable
	char *verificador = ""; //Variable para almacenar la �ltima palabra le�da y poder decidir si se trata de una palabra reservada o un identificador
	bool palabra_detec = false;
	file = fopen(fichero,"r");
	int cont;
	
	//ifstream file(fichero.c_str(), ios:: in ); //Abriendo el archivo
	if (file == NULL) //Si no se encuentra el archivo
		printf("\nEl fichero no existe!! \n\n");
	
	else{ //Si encuentra el archivo
		while((c = fgetc(file)) != EOF){
			printf("%c",c);
		
			if(verificador == " = " && c!= '='){
				
				estado='A';
				verificador="";
			}
			if((verificador=="<"&&(c!='>' || c!='=')) || (verificador==">" && c!='=')){
				printf(" <token_comparador> ");
				estado='A';
				verificador="";
			}
			if(verificador==" > " && c == '>'){
				printf(" <token_simbolo> ");
				estado='A';
				verificador="";
				continue;
			}
			if(verificador=="\"" && c=='"'){
				printf(" <token_cadena> ");
				estado='A';
				verificador="";
				continue;
			}
			if(estado=='F' && !(isdigit(c)) && c!='.'){
				
				estado='A';
				
			}
			if(estado=='G' && ((c)<='0' || (c)>='9')){
				printf(" <token_decimal> ");
				estado='A';
				verificador="";
			}
			char x;
			
			if((estado=='H') && !(isalpha(c)) && !(isdigit(c))){
				for(int cont=0; cont < 12; cont++){
					if(pal_reser[0] =="inicio"){
						printf("TOKEN RESERVADO");
					}else{
						if(pal_reser[1] =="sino"){
							printf(" TOKEN RESERVADO ");
						}else{
							printf(" <token_identificador> ");
						}
					}
					break;
				}
				if(palabra_detec){
					if(verificador=="entero" || verificador=="decimal" || verificador=="cadena"){
						strcpy("tipo_" ,verificador );
						
					}
					printf(" <token_%s> ",verificador);
				}
				palabra_detec=false;
				if(verificador=="fin"){
					printf("\n\n");
					break;
				}
				estado='A';
				verificador="";
			}
			switch(estado){
			case 'A':
				if(c == '='){
					estado = 'B';
					verificador = verificador + c;
				}else if (c == '+' || c == '-' || c == '*' || c == '/'){
					estado = 'C';
					
				}else if(c == '<' || c == '>'|| c == '=='){
					estado= 'I';
					
					verificador = verificador + c;
				}else if (c==';'){
					estado = 'M';
					printf(" <token_punto_coma> ");
					
				}else if (c=='{' || c=='}'){
					estado='M';
					printf(" <token_llave> ");
					//estado='A';
				}else if (c=='(' || c==')'){
					estado='M';
					printf(" <token_parentesis> ");
					estado='A';
				}else if (c=='[' || c==']'){
					estado='M';
					printf(" <token_corchetes> ");
					estado='A';
				}
				else if(c=='"'){
					estado = 'J';
					
				}else if(isdigit(c)){
					estado = 'F';
					verificador=verificador+c;
				}else if(isalpha(c)){
					estado = 'H';
					verificador=verificador+c;
				}else if(c=='\t' || c==' ' || c=='\n'){
					estado = 'Q';
					printf("%c",c);
					estado = 'A';
				}
				else{
					printf(" <token_simbolo> ");
					
				}
				break;
				case 'B':
					printf(" <token_asignacion> ");
					estado = 'A';
					verificador="";
					break;
				case 'C':
					printf(" <token_aritmetico> ");
					estado = 'A';
					break;
				case 'E':
					estado = 'N';
					estado = 'A';
					printf(" <token_comparacion> ");
					verificador="";
					break;
				case 'F':
					if(c!='.'){
						printf(" token_entero ");
						estado='A';
					}else{
						estado='G';
						verificador=verificador+c;
					}					
					break;
				case 'G':
					
					verificador=verificador+c;
					break;
				case 'H':
					//verificador=verificador+c;
					buscarRESERVADOSID;
					break;
				case 'I':
					printf(" <token_relacional> ");
					estado = 'A';
					break;
				case 'J':
					printf(" <token_Comillas> ");
					estado = 'A';
					break;
				case 'M':
					
					estado='A';
					verificador=verificador+c;
					break;
				case 'R':
					buscarRESERVADOSID();
					estado = 'A';
					break;
				default:
					break;
					
				
			}
			
		}
	}
	fclose(file);
	system("pause");
}
	void buscarRESERVADOSID(){
	for(int i=0;i<tamIndicador;i++){
		if(strcmp(pal_reser[i],identificador)==0){
			printf("<TOKEN_%s>",pal_reser[i]);
			identificador[0]='\0';
			break;
		}
		
		if(i==(tamIndicador)-1){printf("\nError no hay ID");exit(-1);}
	}
}
	
	

