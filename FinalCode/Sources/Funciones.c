#include "../Header/MyLib.h"

/*PUNTERO A FUNCION GETKEY: TOMA UNA CADENA Y PROCEDE A LEERLA HASTA ENCONTRAR UN ESPACIO - DEVUELVE LA POSICION DE MEMORIA LUEGO DEL ESPACIO
 *                          Y MODIFICA LA CADENA ORIGINAL
 * Paremeter: char
 * Return: char
 */
char *Getkey (char *key){

	char i=0;

	while (*(key + i) != ' '){ // Busco la posicion del espacio
		i++;
	}

	*(key + i) = 0; // Modifica la cadena original

	return key + i + 1; // Retorna la cadena luego del espacio
}


/*FUNCION INITIALDATA: LECTURA DEL ARCHIVO DE CONFIGURACION Y CARGA DE VALORES A LAS VARIABLES
 * Paremeter: char | TempHum_t (Typedef)
 * Return: void (puntero)
 */
void InitialData (char *fileconfig,TempHum_t *config){
	FILE *confini;
	char cad[50], *value, *key;
	char flagT_set = 0, flagdeltaT = 0, flagH_set = 0, flagdeltaH = 0, flagwarnH = 0;

	// Apertura del archivo de configuracion - En caso de no encontrarlo, se setean valores predeterminados

	if((confini = fopen(fileconfig, "rt")) == NULL){
		printf("***NO se encontro el archivo de configuracion inicial***\n\n");
		config->T_set = 0;
		config->deltaT = 0;
		config->H_set = 0;
		config->deltaH = 0;
		config->warnH = 0;
	}

	fgets (cad, 100, confini); // Lectura del archivo de texto
	do{
		key = cad;

		if ((*key) != '#' && strlen(key) >= 0){ // Condicion para leer una cadena que no sea un comentario

			value = Getkey (key); // value, por medio de la funcion Getkey, toma el valor seteado | Luego de la funcion, key ha sido modificada

			if (!strcmp (key, "T_set") ){
				config->T_set = atoi(value); // Carga de valor a la variable | atoi convierte una cadena a entero
				flagT_set = 1;
			}
			if (!strcmp (key, "deltaT") ){
				config->deltaT = atoi(value); // Carga de valor a la variable | atoi convierte una cadena a entero
				flagdeltaT = 1;
			}
			if (!strcmp (key, "H_set") ){
				config->H_set = atoi(value); // Carga de valor a la variable | atoi convierte una cadena a entero
				flagH_set = 1;
			}
			if (!strcmp (key, "deltaH") ){
				config->deltaH = atoi(value); // Carga de valor a la variable | atoi convierte una cadena a entero
				flagdeltaH = 1;
			}
			if (!strcmp (key, "WarnH")){      // Carga de valor a la variable | atoi convierte una cadena a entero
				config->warnH = atoi(value);
		        flagwarnH = 1;
			}
	   }

	fgets (cad, 100, confini);

	} while (!feof (confini)); // lectura hasta fin de archivo

	fclose(confini);

	if (flagT_set && flagdeltaT && flagH_set && flagdeltaH && flagwarnH) // Si todas las banderas estan en "1", quiere decir que todos los valores se han cargado
        config->PowerOff = 0;                                //  y se retornan los valores en config - Bandera PowerOff = ok

    else {                            // No se cargaron correctamente los valores | Retorna 0 en config
		config->T_set = 0;            // Se procede a apagar la maquina
    	config->deltaT = 0;
    	config->H_set = 0;
    	config->deltaH = 0;
    	config->warnH = 0;
    	config->PowerOff = 1;         // Bandera PowerOff = apagar
    	printf("\n***ERROR la carga de datos desde el archivo de configuracion***\n\n");
    	printf("Se apagara la maquina\n\n");
    	system("pause");
    }
}


/*FUNCION READTEMP: LECTURA DEL SENSOR DE TEMPERATURA (SIMULADO POR TECLADO)
 * Paremeter: void
 * Return: float
 */
float ReadTemp (void){
	float temp;

	fflush(stdin);
	printf("\nTemperatura: ");
	scanf("%f", &temp);

	return temp;
}


/*FUNCION READHUM: LECTURA DEL SENSOR DE HUMEDAD (SIMULADO POR TECLADO)
 * Paremeter: void
 * Return: float
 */
float ReadHum (void){
	float hum;

	fflush(stdin);
    printf("\nHumedad: ");
	scanf("%f", &hum);

    return hum;
}


/*FUNCION HEAT: CALEFACCIONADO DEL SISTEMA (SIMULACION)
 * Paremeter: TempHume_t (Typedef)
 * Return: void
 */
void Heat (TempHum_t temp_1){

	printf("\n\nCalentando | T[actual] =  %.02f°C", temp_1.T);

}


/*FUNCION COOL: REFRIGERACION DEL SISTEMA (SIMULACION)
 * Paremeter: TempHume_t (Typedef)
 * Return: void
 */
void Cool (TempHum_t temp_2){

	printf("\n\nEnfriando | T[actual] =  %.02f°C", temp_2.T);

}


/*FUNCION DRY: VENTILADO DEL SISTEMA (SIMULACION)
 * Paremeter: TempHume_t (Typedef)
 * Return: void
 */
void Dry (TempHum_t hum){

	printf("\n\nVentilando | H[actual] =  %.02f%%", hum.H);

}


/*FUNCION BUZZER: SONIDO DE ALERTA (SIMULACION)
 * Paremeter: void
 * Return: char
 */
char Buzzer (void){

    fflush(stdin);
	printf("<Zumbido>\n");
	printf("Presione 'o' para apagar la alerta: ");

	return getchar();
}

