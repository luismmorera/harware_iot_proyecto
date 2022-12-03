/**
  ******************************************************************************
  * @file   Temperature_sensor.c
  * @author Mario López Parejo (mario.lopezp@alumnos.upm.es)
  * @brief  Temperature Sensor Module header.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "Temperature_sensor.h"             // Module header

/* Private typedef -----------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

float calculo_temperatura_celsius( int registro_temperatura){
  
  return (float)registro_temperatura*0.02 -273.15;
  
}
