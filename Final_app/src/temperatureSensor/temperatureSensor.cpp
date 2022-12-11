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
#include "temperatureSensor.h"             // Module header

/* Private typedef -----------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

const uint8_t MLX90614_I2C_ADDR = 0x5A;
const uint8_t MLX90614_TOBJ1 = 0x07;
const uint8_t SA_W = 0xB4;
const uint8_t MLX90614_REGISTER_SLEEP = 0xFF;
const uint8_t PEC = 0xE8;


int registro_temperatura;
uint8_t buffer_leer[2] = {0,0};
uint8_t buffer_to_sleep[2] = {MLX90614_REGISTER_SLEEP,PEC};
uint8_t wake_up = 0x00;

/* Function prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

float calculo_temperatura_celsius(){ 

  I2C_Device_Read_Data(MLX90614_I2C_ADDR, MLX90614_TOBJ1, buffer_leer, sizeof(buffer_leer));
  registro_temperatura = buffer_leer[0] | (buffer_leer[1] << 8);
  
  return (float)registro_temperatura*0.02 -273.15;
}

void temperature_sensor_to_sleep(){
  I2C_Device_Send_Data (MLX90614_I2C_ADDR, SA_W, buffer_to_sleep, sizeof(buffer_to_sleep));

}

void temperature_sensor_wake_up(){
  I2C_Device_Send_Data(MLX90614_I2C_ADDR,MLX90614_TOBJ1, &wake_up, sizeof(wake_up));
}
