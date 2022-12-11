/**
  ******************************************************************************
  * @file   Time.c
  * @author Mario López Parejo (mario.lopezp@alumnos.upm.es)
  * @brief  Time Module. It access the NTP server and updates the time with a 
  * function to handle waking up from deep sleep mode.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "Time.h"             // Module header

/* Private typedef -----------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

uint8_t dia;
uint8_t horas;
uint8_t minutos;
uint8_t segundos;
uint16_t milisegundos;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

/* Function prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

void init_ntp_client(){
  dia = 0;
  horas = 0;
  minutos = 0;
  segundos = 0;
  milisegundos = 0;
  timeClient.begin();
}

void get_hora_ntp(){
  timeClient.update();
  dia = timeClient.getDay();
  horas = timeClient.getHours() + 1;
  minutos = timeClient.getMinutes();
  segundos = timeClient.getSeconds();
}

/*Si se le pasa un valor superior a 60 segundos funciona mal
 * No creo que sea el objetivo pasarle este valor, ya que el acelerómetro debe actualizar cada menos...
 * Por eso mismo no se ha tratado. Poque sería añadir complejidad a una situacion que nunca se va a dar.
 */
void actualizar_hora(int segundos_sumar){
  uint8_t resultado = segundos + segundos_sumar;
  if (resultado >59){
    segundos = resultado - 60;
    minutos = minutos + 1;
    if (minutos == 60){
      minutos = 0;
      horas = horas + 1;
      if(horas == 24){
        horas = 0;
        dia = dia + 1;
        if(dia == 7){
          dia = 0;
        }
      }
    }
  }else{
    segundos = segundos + segundos_sumar;
  }
}

void actualizar_hora_ms(int milisegundos_sumar){
  uint8_t resultado = milisegundos + milisegundos_sumar;
  if(resultado >= 1000){
	  segundos = segundos + 1;
	  milisegundos = resultado - 1000;
	  if (segundos == 69){
		minutos = minutos + 1;
		if (minutos == 60){
		  minutos = 0;
		  horas = horas + 1;
		  if(horas == 24){
			horas = 0;
			dia = dia + 1;
			if(dia == 7){
			  dia = 0;
			}
		  }
		}
	  }else{
		milisegundos = milisegundos + milisegundos_sumar;
	  }
  }
}

void cambiar_hora(uint8_t hora_act, uint8_t minutos_act, uint8_t segundos_act){
  horas = hora_act;
  minutos = minutos_act;
  segundos = segundos_act;
}


String get_time_hh_mm_ss (){
  return timeClient.getFormattedTime();
 
}
