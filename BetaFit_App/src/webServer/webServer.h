/**
  ******************************************************************************
  * @file   webServer.h
  * @author Pablo San Millán Fierro (pablo.sanmillanf@alumnos.upm.es)
  *			Héctor García Palencia (hector.garpalencia@alumnos.upm.es)
  * @brief  HTTP web server.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the ESP8266 HTTP web server. 
  *         Based on ESP8266WebServer libray.
  ******************************************************************************
*/
#ifndef __webServer_h
#define __webServer_h

  /* Includes ------------------------------------------------------------------*/
    #include <Arduino.h>

    #include "../BetaFit_Debug_Options.h"

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
  
    void webServerBegin();    //Called only once
    
    void webServerLoop();     //Called in every cycle

#endif // __webServer_h