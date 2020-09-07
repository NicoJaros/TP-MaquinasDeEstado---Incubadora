#include "../Header/MyLib.h"


/*FUNCION INITIALDATA: LECTURA DEL ARCHIVO DE CONFIGURACION Y CARGA DE VALORES A LAS VARIABLES
 * Paremeter: char
 * Return: TempHum_t (Typedef)
 */
TempHum_t InitialData (char *fileconfig){
	FILE *confini;
	TempHum_t config;
	char cad[50], *value, *key;
	char varopc[4][25] = {"T_set", "deltaT", "H_set", "deltaH"}, i;
	char flagT_set = 0, flagdeltaT = 0, flagH_set = 0, flagdeltaH = 0;

	// Apertura del archivo de configuracion - En caso de no encontrarlo, se setean valores predeterminados

	if(fopen(fileconfig, "rt") == NULL){
		printf("***NO se encontro el archivo de configuracion inicial***\n\n");
		config.T_set = -127;
		config.deltaT = -127;
		config.H_set = -127;
		config.deltaH= -127;
		return config;
	}

	fgets (cad, 50, confini); // Lectura del archivo de texto
	do{
		key = cad;
		if ((*key) != '#' && strlen(key) >= 0){ // Condicion para leer una cadena que no sea un comentario

			value = Getkey (key); // value, por medio de la funcion Getkey, toma el valor seteado | Luego de la funcion, key ha sido modificada

			for (i=0; i<4; i++){ // i<4 ya que varopc esta "cargada" con 4 cadenas (variables)
				if (!strcmp (key, varopc[i]) ){ // Asigno los valores que tomaran las variables correspondientes
					switch (i){
					case 0:
						config.T_set = atoi(value); // Carga de valor a la variable | atoi convierte una cadena a entero
						flagT_set = 1;
						break;
					case 1:
						config.deltaT = atoi(value);
						flagdeltaT = 1;
						break;
					case 2:
						config.H_set = atoi(value);
						flagH_set = 1;
						break;
					case 3:
						config.deltaH = atoi(value);
						flagdeltaH = 1;
						break;
					}
				}
		   }
	   }
	fgets(cad, 50, confini);

	} while (!feof (confini)); // lectura hasta fin de archivo

	if (flagT_set && flagdeltaT && flagH_set && flagdeltaH){ // Si todas las banderas estan en "1", quiere decir que todos los valores se han cargado
		                                                     //  y se retornan los valores en config
		return config;

	} else { // No se cargaron correctamente los valores | Retorna error en config
		config.T_set = -127;
		config.deltaT = -127;
		config.H_set = -127;
		config.deltaH = -127;
		return config;
	}

}


/*FUNCION READTEMP: LECTURA DEL SENSOR DE TEMPERATURA (SIMULADO POR TECLADO)
 * Paremeter: char
 * Return: void
 */
char ReadTemp (void){
	int temp;

	printf("\nTemperatura: ");
	scanf("%d", &temp);

	return (char) temp;
}


/*FUNCION READHUM: LECTURA DEL SENSOR DE HUMEDAD (SIMULADO POR TECLADO)
 * Paremeter: char
 * Return: void
 */
char ReadHum (void){
	int hum;

    printf("\nHumedad: ");
	scanf("%d", &hum);

    return (char) hum;
}


/*FUNCION HEAT: CALEFACCIONADO DEL SISTEMA (SIMULACION)
 * Paremeter: void
 * Return: TempHume_t (Typedef)
 */
void Heat (TempHum_t temp_1){

	printf("\n\nCalentando | T[actual] =  %.02d°C", temp_1.T);

}


/*FUNCION COOL: REFRIGERACION DEL SISTEMA (SIMULACION)
 * Paremeter: void
 * Return: TempHume_t (Typedef)
 */
void Cool (TempHum_t temp_2){

	printf("\n\nEnfriando | T[actual] =  %.02d°C", temp_2.T);

}


/*FUNCION DRY: VENTILADO DEL SISTEMA (SIMULACION)
 * Paremeter: void
 * Return: TempHume_t (Typedef)
 */
void Dry (TempHum_t hum){

	printf("\n\nEnfriando | H[actual] =  %.02d", hum.H);

}


/*PUNTERO A FUNCION GETKEY: TOMA UNA CADENA Y PROCEDE A LEERLA HASTA ENCONTRAR UN ESPACIO - DEVUELVE LA POSICION DE MEMORIA LUEGO DEL ESPACIO
 *                          Y MODIFICA LA CADENA ORIGINAL
 * Paremeter: char
 * Return: char
 */
char *Getkey (char *key){

	int i,j=0;

	for (i=0; i<50; i++) // Busco la posicion del espacio
		if (*(key + i)!= ' ')
			j++;

	*(key + j) = 0; // Modifica la cadena original

	return key + j +1; // Retorna la cadena luego del espacio
}
