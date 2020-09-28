#include "../Header/MyLib.h"

/*FUNCION CONFIGINIT: INICIO DE PROGRAMA CON LA APERTURA DEL ARCHIVO DE CONFIGURACION
 * Paremeter: TempHum_t (Typedef)
 * Return: void (puntero)
 */
void f_ConfigInit (TempHum_t *configD){

	InitialData ("../Config/Config.conf", configD);

}


/*FUNCION F_WAIT: LECTURA DE SENSORES | DIRECTIVA A PROXIMOS ESTADOS
 * Paremeter: TempHum_t (Typedef)
 * Return: Status_t (Typedef)
 */
Status_t f_wait (TempHum_t config){
	Status_t state = wait;

    printf("-> ");
	config.T = ReadTemp();
	printf("-> ");
	config.H = ReadHum();

    if (config.T < config.T_set - config.deltaT) // Calentar
    	state = f_Heat (config);


    if (config.T > config.T_set + config.deltaT) // Enfriar
    	state = f_Cool (config);


	if (config.H > config.H_set + config.deltaH) // Ventilar
		state = f_Dry (config);

	if (config.H < config.warnH) // Alerta
		state = f_WarningH (config);

	return state;
}


/*FUNCION F_HEAT: LECTURA DE SENSOR | ACTIVACION DEL SISTEMA DE CALEFACCION
 * Paremeter: TempHum_t (Typedef)
 * Return: Status_t (Typedef)
 */
Status_t f_Heat (TempHum_t config){
	Status_t state;

	Heat (config);
	do{
		config.T = ReadTemp(); // Simulacion de lectura del sensor
	}
	while (config.T <= config.T_set + (config.deltaT/2));   // Ejecucion de la funcion hasta lograr la temperatura deseada

	return state = wait;  // Vuelta al estado de espera
}


/*FUNCION F_COOL: LECTURA DE SENSOR | ACTIVACION DEL SISTEMA DE REFRIGERACION
 * Paremeter: TempHum_t (Typedef)
 * Return: Status_t (Typedef)
 */
Status_t f_Cool (TempHum_t config){
	Status_t state;

	Cool (config);
	do{
		config.T = ReadTemp();  // Simulacion de lectura del sensor
	}
	while (config.T >= config.T_set - (config.deltaT/2));   // Ejecucion de la funcion hasta lograr la temperatura deseada

	return state = wait;  // Vuelta al estado de espera
}


/*FUNCION F_DRY: LECTURA DE SENSOR | ACTIVACION DEL SISTEMA DE VENTILACION
 * Paremeter: TempHum_t (Typedef)
 * Return: Status_t (Typedef)
 */
Status_t f_Dry (TempHum_t config){
	Status_t state;

	Dry (config);
	do{
		config.H = ReadHum();  // Simulacion de lectura del sensor
	}
	while (config.H >= config.H_set - (config.deltaH/2));// Ejecucion de la funcion hasta lograr la humedad deseada

	return state = wait;  // Vuelta al estado de espera
}


/*FUNCION F_WARNING: ALERTA POR BAJA HUMEDAD | SIMULACION DE SONIDO
 * Paremeter: TempHume_t (Typedef)
 * Return: void
 */
Status_t f_WarningH (TempHum_t config){
	Status_t state;
	char Alert;

	printf("\n\n***ALERTA: HUMEDAD BAJA***\n");
	Alert = Buzzer();     // Activacion de alerta sonora | A la espera de que el usuario la apague
	if (Alert == 'o'){
		return state = wait;
	}

	return state = f_WarningH (config);  // Si el usuario no apaga la alarma, se vuelve a invocar la funcion
}
