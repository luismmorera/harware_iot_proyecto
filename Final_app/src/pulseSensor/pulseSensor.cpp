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
#include "pulseSensor.h"             // Module header

int periodo_muestreo  = 10;
int duracion_medida   = 30000;
int tiempo_set_up     = 10000;
int tiempo_transitorio = 5000;

int media;
int contador_pulsos;
int tension_entrada;

float maximo;

int heart_rate;
bool primera_deteccion;

/* Private typedef -----------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/


void init_hr_sensor(int pin_alimentacion, bool init_medida, bool fin_medida, bool fin_transitorio){
  pinMode(pin_alimentacion,OUTPUT);
  pinMode(A0,INPUT);
  digitalWrite(pin_alimentacion, HIGH);
  fin_medida = false;
  init_medida = false;
  contador_pulsos = 0;
  media = 0;
  tension_entrada = 0;
  maximo = 0;
  primera_deteccion = true;
  fin_transitorio = false;
  heart_rate = -1;
}


int realizar_medidas(bool init_medida, bool fin_medida, bool fin_transitorio){
  if(fin_transitorio){
    if(!fin_medida && init_medida){
      tension_entrada = 600 + (analogRead(A0) - (media*0.002))*300 ; // +1000
      if(tension_entrada > maximo){
        maximo = tension_entrada; // valor cercano a 2200
        //Serial.println(maximo);
      }
      Serial.println(maximo);
      Serial.println(tension_entrada);
      if(tension_entrada > maximo*0.60){
        if(primera_deteccion){
          contador_pulsos++;
          Serial.println(contador_pulsos);
          primera_deteccion = false;
        }
      }else if(tension_entrada < maximo*0.25){ //Dejo aquí una tierra de nadie para las oscilaciones.
        primera_deteccion = true;
      }    
    }else if(!fin_medida && !init_medida && fin_transitorio){
      media = media + (analogRead(A0));
      Serial.println(media);
    
    }else{
      if(contador_pulsos*3 < 20 || contador_pulsos*3 > 200){ //Se ha producido un error en la medida.
        heart_rate = 1;
      }else{
        heart_rate = contador_pulsos*3;                  //Medida correcta.
      }
    }
  }
  return heart_rate;
}

void switch_off_hr_sensor(int pin_alimentacion){
  digitalWrite(pin_alimentacion, LOW);
}
/*
void avisar_fin_transitorio(bool fin_transitorio){
  fin_transitorio = true;
}

void deshabilitarMedida(bool fin_medida){
  fin_medida = true;
}

void iniciar_Medida(bool init_medida){
  init_medida = true;
}*/
