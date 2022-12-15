/**
  ******************************************************************************
  * @file   BetaFit_Temperature_Sensor_Module.cpp
  * @author Mario López Parejo (mario.lopezp@alumnos.upm.es)
  * @brief  Temperature Sensor module.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manage the temperature sensor (GY906 - MLX90614).
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "BetaFit_Temperature_Sensor_Module.h" // Module header

/* Private typedef -----------------------------------------------------------*/

// I2C Device Adress
#define MLX90614_I2C_ADDR 0x5A

// Register address
#define MLX90614_REGISTER_SLEEP 0xFF

// Sensor RAM Memory address
#define MLX90614_TOBJ1_ADDR 0x07

// Register values
#define SA_W 0xB4
#define PEC  0xE8

/* Private variables----------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
float Get_Temperature_Celsius (void);

void Temperature_Sensor_Sleep  (void);

void Temperature_Sensor_WakeUp (void);

/* Functions -----------------------------------------------------------------*/

/**
* @brief This function get raw temperature data form the sensor and then calculate
*        the temperature in degrees Celsius to one decimal place of accuracy.
*
* @retval (float) temperature in degrees Celsius to one decimal place of accuracy.
*/
float Get_Temperature_Celsius (void) {

  uint8_t buffer[2] = {0, 0};

  uint16_t registro_temperatura = 0;

  I2C_Device_Read_Data(MLX90614_I2C_ADDR, MLX90614_TOBJ1, buffer, sizeof(buffer));
  
  registro_temperatura = (buffer[1] << 8) | buffer[0];
  
  return (float) ((registro_temperatura*0.02) - 273.15);
}

/**
* @brief This function communicates to the temperature sensor to be turned off.
*
* @retval none.
*/
void Temperature_Sensor_Sleep (void) {

  uint8_t buffer[2] = {MLX90614_REGISTER_SLEEP, PEC}

  I2C_Device_Send_Data (MLX90614_I2C_ADDR, SA_W, buffer, sizeof(buffer));
}

/**
* @brief This function communicates to the temperature sensor to wake up.
*
* @retval none.
*/
void Temperature_Sensor_WakeUp (void) {
  
  uint8_t wake_up = 0x00;

  I2C_Device_Send_Data(MLX90614_I2C_ADDR, MLX90614_TOBJ1, &wake_up, sizeof(wake_up));
}