#include "../Header/MyLib.h"

/*FUNCION CONFIGINIT: INICIO DE PROGRAMA CON LA APERTURA DEL ARCHIVO DE CONFIGURACION
 * Paremeter: void
 * Return: TempHum_t (Typedef)
 */
TempHum_t f_ConfigInit (void){
	TempHum_t config;

	config = InitialData ("../Config/Config.conf");
	config.PowerOff = 0;

	// SI NO ES POSIBLE LA CARGA DE DATOS, SE APAGARA EL SISTEMA
	if ((config.T_set = -127) || (config.deltaT = -127) || (config.H_set = -127) || (config.deltaH = -127)){
		printf("***Error en la carga de datos desde el archivo de configuracion***\n");
		printf("Se apagara el sistema\n\n");
		system("pause");
		config.PowerOff = 1;
		return config;
	}

	return config;
}


/*FUNCION F_WAIT: LECTURA DE SENSORES | DIRECTIVA A PROXIMOS ESTADOS
 * Paremeter: Status_t (Typedef)
 * Return: TempHum_t (Typedef)
 */
Status_t f_wait (TempHum_t config){
	Status_t state = wait;

	config.T = ReadTemp();
	config.H = ReadHum();

    if (config.T < config.T_set - config.deltaT) // Calentar
    	state = f_Heat (config);


    if (config.T > config.T_set + config.deltaT) // Enfriar
    	state = f_Cool (config);


	if (config.H > config.H_set + config.deltaH) // Ventilar
		state = f_Dry (config);

	return state;
}


/*FUNCION F_HEAT: LECTURA DE SENSOR | ACTIVACION DEL SISTEMA DE CALEFACCION
 * Paremeter: Status_t (Typedef)
 * Return: TempHum_t (Typedef)
 */
Status_t f_Heat (TempHum_t config){
	Status_t state;
	config.T = ReadTemp();
	Heat (config);
	state = heat;

	if(config.T > config.T_set + (config.deltaT/2))
		state = wait;

	return state;
}


/*FUNCION F_COOL: LECTURA DE SENSOR | ACTIVACION DEL SISTEMA DE REFRIGERACION
 * Paremeter: Status_t (Typedef)
 * Return: TempHum_t (Typedef)
 */
Status_t f_Cool (TempHum_t config){
	Status_t state;
	config.T = ReadTemp();
	Cool (config);
	state = cool;

	if(config.T < config.T_set - (config.deltaT/2))
		state = wait;

	return state;
}


/*FUNCION F_DRY: LECTURA DE SENSOR | ACTIVACION DEL SISTEMA DE VENTILACION
 * Paremeter: Status_t (Typedef)
 * Return: TempHum_t (Typedef)
 */
Status_t f_Dry (TempHum_t config){
	Status_t state;
	config.T = ReadHum();
	Dry (config);
	state = dry;

	if(config.H < config.H_set - (config.deltaH/2))
		state = wait;

	return state;
}
