/**
  ******************************************************************************
  * @file   wifiConnection.h
  * @author Pablo San Millán Fierro (pablo.sanmillanf@alumnos.upm.es)
  * @brief  WiFi connection handler.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the ESP8266 WiFi connection and all the feautres 
  *         related to it: the web server. Based on ESP8266WiFi libray.
  ******************************************************************************
*/
#ifndef __wifiConnection_h
#define __wifiConnection_h

  /* Includes ------------------------------------------------------------------*/
    #include <Arduino.h>

    #include "../BetaFit_Debug_Options.h"

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
    
    void wifiConnectionStart(String ssid, String password);
    
    void wifiConnectionStop();

#endif // __wifiConnection_h