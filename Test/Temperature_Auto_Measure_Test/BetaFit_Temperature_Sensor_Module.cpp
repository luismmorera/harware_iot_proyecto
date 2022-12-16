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

#include "BetaFit_I2C_Module.h" // I2C Module header

/* Private typedef -----------------------------------------------------------*/
#define __BetaFit_Temperature_Sensor_Module_Debug_Mode

// I2C Device Adress
#define MLX90614_I2C_ADDR 0x5A

// Register address
#define MLX90614_REGISTER_SLEEP 0xFF

// Sensor RAM Memory address
#define MLX90614_TOBJ1_ADDR 0x07

// Register values
#define MLX90614_SA_W 0xB4
#define MLX90614_PEC  0xE8

/* Private variables----------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
float Get_Temperature_Celsius (void);

void Temperature_Sensor_Sleep  (void);

void Temperature_Sensor_WakeUp (void);

/* Functions -----------------------------------------------------------------*/

/**
  * @brief This function initialize the I2C resources and check that the temperature
  *        sensor is available.
  *
  * @retval none.
  */
void Temperature_Sensor_Begin (void) {

  I2C_Device_Begin( );

  if (!I2C_Device_Detected(MLX90614_I2C_ADDR)) {
    #ifdef __BetaFit_Temperature_Sensor_Module_Debug_Mode
      Serial.println(F("Temperature Sensor allocation failed"));
    #endif
    for(;;); // Don't proceed, loop forever
  }

  #ifdef __BetaFit_Temperature_Sensor_Module_Debug_Mode
    Serial.println(F("Temperature Sensor allocation succes"));
  #endif
}

/**
  * @brief This function get raw temperature data form the sensor and then calculate
  *        the temperature in degrees Celsius to one decimal place of accuracy.
  *
  * @retval (float) temperature in degrees Celsius to one decimal place of accuracy.
  */
float Get_Temperature_Celsius (void) {

  uint8_t buffer[2] = {0, 0};

  uint16_t registro_temperatura = 0;

  I2C_Device_Read_Data(MLX90614_I2C_ADDR, MLX90614_TOBJ1_ADDR, buffer, sizeof(buffer));
  
  registro_temperatura = (buffer[1] << 8) | buffer[0];
  
  return (float) ((registro_temperatura*0.02) - 273.15);
}

/**
  * @brief This function communicates to the temperature sensor to be turned off.
  *
  * @retval none.
  */
void Temperature_Sensor_Sleep (void) {

  uint8_t buffer[2] = {MLX90614_REGISTER_SLEEP, MLX90614_PEC};

  I2C_Device_Send_Data (MLX90614_I2C_ADDR, MLX90614_SA_W, buffer, sizeof(buffer));
}

/**
  * @brief This function communicates to the temperature sensor to wake up.
  *
  * @retval none.
  */
void Temperature_Sensor_WakeUp (void) {
  
  uint8_t wake_up = 0x00;

  I2C_Device_Send_Data(MLX90614_I2C_ADDR, MLX90614_TOBJ1_ADDR, &wake_up, sizeof(wake_up));

  delay(15);
}
