/**
  ******************************************************************************
  * @file   flash.h
  * @author Pablo San Millán Fierro (pablo.sanmillanf@alumnos.upm.es)
  * @brief  Flash manager with SPI FFS.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the ESP8266 flash memory.
  ******************************************************************************
*/
#ifndef __flash_h
#define __flash_h

  /* Includes ------------------------------------------------------------------*/
  #include <Arduino.h>
  
  #include "../BetaFit_Debug_Options.h"

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
  void flashBegin();
  String readFile(String path);
  bool writeFile(String path, String text);

#endif // __flash_h