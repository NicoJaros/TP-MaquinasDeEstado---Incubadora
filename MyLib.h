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
  char T, H;             //      T: Temperatura actual   | H: Humedad actual
  char T_set, H_set;     //  T_set: Temperatura seteada  | H_set: Humedad seteada
  char deltaT, deltaH;   // deltaT: Delta de temperatura | deltaH: Delta de humedad
  char PowerOff;         // Apagado del sistema
} TempHum_t;

Status_t (*MachineState[4])(TempHum_t); // Puntero a Funciones (ESTADOS)


// Funciones de la maquina de estado

TempHum_t f_ConfigInit (void);   // Funcion de Estado: Inicio de la maquina
Status_t f_wait (TempHum_t);     // Funcion de Estado: espera
Status_t f_Heat (TempHum_t);     // Funcion de Estado: calefaccionar
Status_t f_Cool (TempHum_t);     // Funcion de Estado: refrigerar
Status_t f_Dry (TempHum_t);      // Funcion de Estado: ventilar


//Funciones particulares

char *Getkey (char *key);
TempHum_t InitialData (char *);     // Carga de valores pre-seteados
char ReadTemp (void);               // Sensor de Temperatura (simulado)
char ReadHum (void);                // Sensor de Humedad (simulado)
void Heat (TempHum_t Temp_1);       // Accionamiento de la calefaccion (simulado)
void Cool (TempHum_t Temp_2);       // Accionamiento de la refrigeracion (simulado)
void Dry (TempHum_t Hum);           // Accionamiento de la ventilacion (simulado)


#endif /* HEADER_MYLIB_H_ */
