/**
  ******************************************************************************
  * @file   BetaFit_RTC_Module.h
  * @author Mario López Parejo (mario.lopezp@alumnos.upm.es)
  * @brief  RTC Module header.
  *         
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         
  ******************************************************************************
*/
#ifndef __BetaFit_RTC_Module_h
#define __BetaFit_RTC_Module_h

  /* Includes ------------------------------------------------------------------*/
    #include <Arduino.h>

    #include "../BetaFit_Debug_Options.h"

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
  
    /**
      * @brief    Función que se encarga de conectarse al servidor NTP y actualizar la hora del 
      *           RTC según la información obtenida del NTP.
      *
      * @retval   true si se ha realizado la actualización de hora de forma correcta, false
      *           en caso contrario.
      */
    extern bool RTC_Device_Begin (const char *ssid, const char *password);

    /**
      * @brief    Función que accede al registro del RTC y devuelve el año.
      */
    extern uint16_t get_Year(void);

    /**
      * @brief    Función que accede al registro del RTC y devuelve el mes.
      */
    extern uint8_t get_Month(void);

    /**
      * @brief    Función que accede al registro del RTC y devuelve el dia de mes.
      *           La función de la librería que devuelve el día de la semana no se emplea al no ser necesario.
      */
    extern uint8_t get_Day(void);

    /**
      * @brief    Función que accede al registro del RTC y devuelve la hora actual.
      */
    extern uint8_t get_Hours(void);

    /**
      * @brief    Función que accede al registro del RTC y devuelve los minutos.
      */
    extern uint8_t get_Minutes(void);

    /**
      * @brief    Función que accede al registro del RTC y devuelve los segundos.
      */
    extern uint8_t get_Seconds(void);

#endif // __BetaFit_RTC_Module_h
