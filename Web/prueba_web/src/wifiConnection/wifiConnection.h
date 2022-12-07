/**
  ******************************************************************************
  * @file   wifiConnection.h
  * @author Pablo San Millán Fierro (pablo.sanmillanf@alumnos.upm.es)
  * @brief  Wifi connection handler.
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

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
  void wifiConnectionBegin(String ssid, String password);    //Called only once
  void wifiConnectionRestart(String ssid, String password);
  void wifiConnectionStop();
  void wifiConnectionLoop();     //Called in every cycle

#endif // __wifiConnection_h