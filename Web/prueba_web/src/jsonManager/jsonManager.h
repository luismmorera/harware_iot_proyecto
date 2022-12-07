/**
  ******************************************************************************
  * @file   jsonManager.h
  * @author Pablo San Millán Fierro (pablo.sanmillanf@alumnos.upm.es)
  * @brief  JSON files manager.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the JSON files located in the ESP8266 flash memory.
  *         Based on ArduinoJson libray.
  *         Should be used after flashBegin() call.
  ******************************************************************************
*/
#ifndef __jsonManager_h
#define __jsonManager_h

  /* Includes ------------------------------------------------------------------*/
  #include <Arduino.h>

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
void setHeartRateEntry(String tiempo, float valor, bool alarma);
void setTemperatureEntry(String tiempo, float valor, bool alarma);
void setStepsEntry(uint8_t mes, uint8_t dia, uint32_t valor);
void setCredentials(String usr, String psw);
bool compareCredentials(String usr, String psw);
void setGeneralSettings(String temperatura, String frecuencia);
void setUserSettings(String nombre, String apellido1, String apellido2, String altura, String peso);

#endif // __jsonManager_h