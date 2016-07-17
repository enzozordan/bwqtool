/* bwqtool.c
   (c) 2016 - Enzo Santiago Zordan
   Lee archivo csv (separado por comas, ver archivo.csv) con el objetivo de:
   - Encontrar la ultima linea del archivo (indicador de nueva linea es el codigo ascii 13 - o en hexa: 0D)
   - Encontrar los primeros 26 valores numericos flotantes que se encuentran entre la coma numero 47 y 48
   - Calcular el promedio entre los primeros 13 valores y los restantes 13 valores
   - Guardar el valor de cada promedio en dos variables y mostrarlas en pantalla
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *archivo;
	char c;							//caracter leido de archivo csv
	char valor[7];					//reservo 7 caracteres para valor de densidad
	float valores[26];				//declaro vector de valores reales con 26 pistas
	int comas = 0;					//contador de comas para detectar la columna 48 (despues de coma 47)
	int existe_punto = 0;			//bandera para saber si la variable valor contiene un punto
	int i = 0;						//var aux generica
	int pista = 0;					//contador de pistas (para no tener en cuenta pista>26 que son siempre cero)
	int barrido = 0;				//cantidad de barridos o mediciones en el archivo
	int linea = 0;					//cantidad de lineas (suponiendo que cada una termina con el ascii 13 (o OD))
	int eslaultima = 0;				//bandera para saber si estoy en la ultima linea
	float promedio_izquierda = 0.0;	//promedio de 13 pistas de la izquierda
	float promedio_derecha = 0.0;	//promedio de 13 pistas de la derecha

	archivo = fopen("archivo.csv","r");
	
	while((c=fgetc(archivo))!=EOF) //mientras no sea el final del archivo
	{
		if(c == 13) {linea++;} //cuento la cantidad de lineas que tiene el archivo
	}
	fclose(archivo);


	for(i=0;i<7;i++)
	{
		valor[i] = '0'; //inicializo el vector de caracteres con caracteres 0
	}
	for(i=0;i<26;i++)
	{
		valores[i] = 0.0; // inicializo cada posicion del vector de densidades con 0.0
	}
	i = 0;
	archivo = fopen("archivo.csv","r"); //abro el archivo csv
	while((c=fgetc(archivo))!=EOF) //mientras no sea el final del archivo
	{
		if(c == 13)	//si encuentro un final de linea
		{
			barrido++; //incremento contador de lineas actuales
			if((linea-1) == barrido) //busco leer la ultima linea agregada por bwq2000
			{
				eslaultima = 1; //seteo bandera a 1 para saber que estoy en la ultima linea
			}
		}
		if(eslaultima == 1) //si estoy en la ultima
		{
			if(c == ',')
			{
				comas++; //si es una coma entonces incremento el contador de comas
			}
			if(comas == 47) //si estoy despues de la coma 47 que es donde estan las densidades, entonces
			{
				if(c != ',') //si estoy entre la coma 47 y la 48
				{
					if(c != ' ') 
					{
						valor[i] = c; //si no es un espacio supongo que es un numero o un punto y lo guardo
						i++;
					}
					else //si es un espacio
					{
						for(i=0;i<7;i++)
						{
							if(valor[i] == '.')
							{
								existe_punto = 1; //recorro el arreglo de caracteres para ver si guarde un punto
							}
						}		
						if(existe_punto == 1) //si habia un punto entonces
						{
							if(pista <= 25)
							{
								valores[pista] = atof(valor); //convierto la cadena en flotante y lo guardo en vector
								pista++;	
							}
							else
							{
								break; // si me encuentro en la muestra 27 termino el programa ya que supongo que
							}          // a partir de la muestra 27 los valores son todos 0.0   
						}				
						for(i=0;i<7;i++)
						{
							valor[i] = '0'; //inicializo el arreglo de caracteres con caracteres 0
						}
						i = 0;
						existe_punto = 0;
					}
				}
			}
		}
	}
	fclose(archivo); //cierro el archivo para que otros programas puedan usarlo

	for(i=0;i<=12;i++)
	{
		promedio_izquierda += valores[i]; //calculo el promedio
	}
	for(i=13;i<=25;i++)
	{
		promedio_derecha += valores[i]; //calculo el promedio
	}
	promedio_izquierda = promedio_izquierda / 13.0; //promedio izquierdo
	promedio_derecha = promedio_derecha / 13.0;     //promedio derecho

	printf("%.2f, %.2f\n",promedio_izquierda,promedio_derecha); //muestro promedios

	return 0;
}