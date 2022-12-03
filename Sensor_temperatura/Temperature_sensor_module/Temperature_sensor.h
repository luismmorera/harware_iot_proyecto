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
#ifndef __Temperature_sensor_h
#define __Temperature_sensor_h

  /* Includes ------------------------------------------------------------------*/
  #include "BetaFit_I2C_Module.h"

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
  float calculo_temperatura_celsius( int registro_temperatura);

#endif // __BetaFit_I2C_Module_h
