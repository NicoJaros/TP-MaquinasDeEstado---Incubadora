#include "../Header/MyLib.h"

int main(){

    TempHum_t configMain, *Data;
    Status_t state = wait;     // Primer estado
    Status_t (*MachineState[])(TempHum_t) = {f_wait, f_Heat, f_Cool, f_Dry};      // Punteros a funciones de estado

    Data = &configMain;          // Puntero pasaje por referencia
    configMain.PowerOff = 0;     // Encendido de la maquina

    f_ConfigInit (Data); // Carga de valores pre-seteados

    if (configMain.PowerOff == 1) // Apagado de la maquina
    	return 0;

    while(1){
    	state = (*MachineState[state])(configMain); // Ejecucion continua de la maquina
    }

	return 0;
}
