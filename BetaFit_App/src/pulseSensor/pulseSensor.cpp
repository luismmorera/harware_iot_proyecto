/**
  ******************************************************************************
  * @file   Pulse_sensor.c
  * @author Mario López Parejo (mario.lopezp@alumnos.upm.es)
  * @brief  Analog Pulse Sensor Module header.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "pulseSensor.h" // Module header  

// Standard Libraries
#include <stdint.h>

// BetaFit Libraries
#include "../BetaFit_Hardware.h"

/* Private typedef -----------------------------------------------------------*/

//Si se quiere optimizar aún más se puede jugar con los múltiplos de TIEMPO_TRANSITORIO.
 #define TIEMPO_TRANSITORIO  500
 #define TIEMPO_ESTABLECIMIENTO_MEDIA  1000
 #define TIEMPO_MEDIDA  3000

/* Private variables----------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

void init_hr_sensor (void) {
  pinMode(D5_PIN, OUTPUT);
  pinMode(A0, INPUT);
}

uint8_t realizar_medidas(){
  int tension_entrada;
  uint16_t contador_intervalo_muestreo = 0;
  uint8_t contador_pulsos = 0;
  uint16_t heart_rate = 0;
  int media = 0;
  float maximo = 0;
  bool primera_deteccion = true;

  digitalWrite(D5_PIN, HIGH);
   
  while(contador_intervalo_muestreo <= TIEMPO_MEDIDA){
    if(contador_intervalo_muestreo  >= TIEMPO_TRANSITORIO){
      if(contador_intervalo_muestreo > TIEMPO_ESTABLECIMIENTO_MEDIA && contador_intervalo_muestreo < TIEMPO_MEDIDA){
        tension_entrada = 600 + (analogRead(A0) - (media*0.002))*300 ; // +1000
        if(tension_entrada > maximo){
          maximo = tension_entrada; // valor cercano a 2200
        }

        #ifdef __pulseSensor_Debug_Mode
          Serial.println(maximo);
          Serial.println(tension_entrada);
        #endif

        if(tension_entrada > maximo*0.65){
          if(primera_deteccion){
            contador_pulsos++;

            #ifdef __pulseSensor_Debug_Mode
              Serial.println(contador_pulsos);
            #endif

            primera_deteccion = false;
          }
          
        } else if(tension_entrada < maximo*0.25){ //Dejo aquí una tierra de nadie para las oscilaciones.
          primera_deteccion = true;
        }
            
      } else if(contador_intervalo_muestreo > TIEMPO_TRANSITORIO && contador_intervalo_muestreo <= TIEMPO_ESTABLECIMIENTO_MEDIA){
        media = media + (analogRead(A0));
        
        #ifdef __pulseSensor_Debug_Mode
          Serial.println(media);
        #endif
    
      } else if (contador_intervalo_muestreo >= TIEMPO_MEDIDA) {

        if(contador_pulsos*3 < 30 || contador_pulsos*3 > 200) { //Se ha producido un error en la medida.
          heart_rate = 1;
        }else{
          heart_rate = contador_pulsos*3;                  //Medida correcta.
        }
      }
    }
    contador_intervalo_muestreo++;
    delay(10);
  }

  digitalWrite(D5_PIN, LOW);

  return heart_rate;
}
