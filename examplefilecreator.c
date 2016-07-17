/* examplefilecreator.c
   (c) 2016 - Enzo Santiago Zordan 
   Crea un archivo csv de ejemplo con formato identico al que procesa bwqtool.c
   La informacion que interesa extraer se encuentra despues de la coma 47.
   Los valores que se encuentran entre la coma 47 y la 48 estan separados por espacios.
   Cada final de linea esta dado por el ascii ODh
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *archivo;
	char finaldelinea = 13;	//0Dh	
	int i,j,k;					

	archivo = fopen("archivo.csv", "ab+");//"ab+");

	for(i=0;i<4;i++) //3 lineas
	{
		for(j=0;j<=50;j++) //50 comas
		{
			fprintf(archivo,",");
			if(j==46) //si estoy en la coma 47
			{
				for(k=0;k<40;k++) //escribo 40 valores (solo interesan los primeros 26)
				{
					fprintf(archivo,"3.03 "); //bwqtool.c deberia dar un promedio de 3.03
				}
			}
		}
	fprintf(archivo,"%c",finaldelinea);
	}

	fclose(archivo);

	return 0;
}