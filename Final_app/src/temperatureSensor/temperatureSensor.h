/**
  ******************************************************************************
  * @file   Temperature_sensor.h
  * @author Mario López Parejo (mario.lopezp@alumnos.upm.es)
  * @brief  Temperature Sensor Module header.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         
  ******************************************************************************
*/
#ifndef __temperatureSensor_h
#define __temperatureSensor_h

  /* Includes ------------------------------------------------------------------*/
  #include "BetaFit_I2C_Module.h"

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
  
  /**
   * Función que devuelve la temperatura en grados celsius con un decimal de precisión.
   */
  float calculo_temperatura_celsius();
  
   /**
   * Función que pone en modo reposo al sensor de temperatura.
   */
  void temperature_sensor_to_sleep();
  
   /**
   * Función que despierta al sensor de temperatura para realizar nuevas medidas.
   */
  void temperature_sensor_wake_up();

#endif // __BetaFit_I2C_Module_h
