#ifndef HEADER_MYLIB_H_
#define HEADER_MYLIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {   // Tipo Numerativo para los posibles estados de la maquina
  wait = 0,
  heat = 1,
  cool = 2,
  dry = 3,
} Status_t;

typedef struct {
  float T, H;            //      T: Temperatura actual   | H: Humedad actual
  int T_set, H_set;      //  T_set: Temperatura seteada  | H_set: Humedad seteada
  int deltaT, deltaH;    // deltaT: Delta de temperatura | deltaH: Delta de humedad
  int warnH;             // WarnH: alerta de baja humedad
  char PowerOff;         // Apagado del sistema
} TempHum_t;

Status_t (*MachineState[4])(TempHum_t *); // Puntero a Funciones (ESTADOS)


// Funciones de la maquina de estado

void f_ConfigInit (TempHum_t *);        // Funcion de Estado: Inicio de la maquina
Status_t f_wait (TempHum_t);            // Funcion de Estado: espera
Status_t f_Heat (TempHum_t);            // Funcion de Estado: calefaccionar
Status_t f_Cool (TempHum_t);            // Funcion de Estado: refrigerar
Status_t f_Dry (TempHum_t);             // Funcion de Estado: ventilar
Status_t f_WarningH (TempHum_t);        // Funcion de Estado: alerta


//Funciones particulares

char *Getkey (char *key);
void InitialData (char *, TempHum_t *);     // Carga de valores pre-seteados
void PowerOff (TempHum_t *);                // Comprobacion de carga de datos
float ReadTemp (void);                      // Sensor de Temperatura (simulado)
float ReadHum (void);                       // Sensor de Humedad (simulado)
void Heat (TempHum_t Temp_1);               // Accionamiento de la calefaccion (simulado)
void Cool (TempHum_t Temp_2);               // Accionamiento de la refrigeracion (simulado)
void Dry (TempHum_t Hum);                   // Accionamiento de la ventilacion (simulado)
char Buzzer (void);                         // Sonido de alarma por baja humedad


#endif /* HEADER_MYLIB_H_ */
