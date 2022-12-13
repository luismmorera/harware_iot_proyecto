/**
  ******************************************************************************
  * @file   BetaFit_Temperature_Sensor_Module.h
  * @author Mario López Parejo (mario.lopezp@alumnos.upm.es)
  * @brief  Temperature Sensor module header.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manage the temperature sensor (GY906 - MLX90614).
  ******************************************************************************
*/
#ifndef __BetaFit_Temperature_Sensor_Module_h
#define __BetaFit_Temperature_Sensor_Module_h

  /* Includes ------------------------------------------------------------------*/
  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
  
    /**
      * @brief This function get raw temperature data form the sensor and then calculate
      *        the temperature in degrees Celsius to one decimal place of accuracy.
      *
      * @retval (float) temperature in degrees Celsius to one decimal place of accuracy.
      */
    extern float Get_Temperature_Celsius (void);

    /**
      * @brief This function communicates to the temperature sensor to be turned off.
      *
      * @retval none.
      */
    extern void Temperature_Sensor_Sleep (void);

    /**
      * @brief This function communicates to the temperature sensor to wake up.
      *
      * @retval none.
      */
    extern void Temperature_Sensor_WakeUp (void);

#endif // __BetaFit_Temperature_Sensor_Module_h
