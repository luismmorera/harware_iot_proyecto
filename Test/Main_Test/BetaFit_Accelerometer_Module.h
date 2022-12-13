/**
  ******************************************************************************
  * @file   BetaFit_Accelerometer_Module.h
  * @author Juan Morales Sáez (j.msaez@alumnos.upm.es)
  * @brief  Accelerometer Module header.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the OLED module.
  ******************************************************************************
*/

#ifndef __BetaFit_Accelerometer_Module_h
#define __BetaFit_Accelerometer_Module_h

  #define __BetaFit_Accelerometer_Module_Debug_Mode

  /* Includes ------------------------------------------------------------------*/
  #include <Arduino.h>
  #include <Adafruit_MMA8451.h>
  #include <Adafruit_Sensor.h>

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  #define BETAFIT_ON_POSITION  0x01
  #define BETAFIT_OFF_POSITION 0x10
  
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
  extern void Accelerometer_Device_Begin (void);

  extern void Accelerometer_Update_Acceleration_Data (void);

  extern uint8_t Accelerometer_Get_Position (void);

#endif // __BetaFit_Accelerometer_Module_h
