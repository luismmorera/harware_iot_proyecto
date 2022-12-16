/**
  ******************************************************************************
  * @file   BetaFit_Accelerometer_Module.h
  * @author Juan Morales Sáez (j.msaez@alumnos.upm.es)
  * @brief  Accelerometer Module header.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the accelerometer (MMA451).
  ******************************************************************************
*/

#ifndef __BetaFit_Accelerometer_Module_h
#define __BetaFit_Accelerometer_Module_h

  #define __BetaFit_Accelerometer_Module_Debug_Mode

  /* Includes ------------------------------------------------------------------*/
  #include <Arduino.h>
  #include <Adafruit_MMA8451.h>
  #include <Adafruit_Sensor.h>

  #include "BetaFit_SetpDetector_Module.h"

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  #define BETAFIT_ON_POSITION      0x01
  #define BETAFIT_OFF_POSITION     0x02
  #define BETAFIT_MEAS_BH_POSITION 0x03
  
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
    /**
      * @brief This function initialize the accelerometer resources and check that 
      *        the accelerometer is available.
      *
      * @retval none.
      */
    extern void Accelerometer_Device_Begin (void);

    /**
      * @brief This function initialize the accelerometer resources and check that 
      *        the accelerometer is available.
      *
      * @retval none.
      */
    extern void Accelerometer_Update_Acceleration_Data (void);
    
    /**
      * @brief This function initialize the accelerometer resources and check that 
      *        the accelerometer is available.
      *
      * @retval none.
      */
    extern uint8_t Accelerometer_Get_Position (void);

#endif // __BetaFit_Accelerometer_Module_h
