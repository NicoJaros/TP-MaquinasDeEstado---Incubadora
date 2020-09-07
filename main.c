#include "../Header/MyLib.h"

int main(){

    TempHum_t config;
    Status_t state = wait; // Primer estado

    Status_t (*MachineState[])(TempHum_t) = {f_wait, f_Heat, f_Cool, f_Dry}; // Punteros a funciones de estado

    config = f_ConfigInit(); // Carga de valores pre-seteados

    if (config.PowerOff == 1) // Apagado de la maquina
    	return 0;

    while(1){
    	state = (*MachineState[state])(config); // Ejecucion continua de la maquina
    }

	return 0;
}
