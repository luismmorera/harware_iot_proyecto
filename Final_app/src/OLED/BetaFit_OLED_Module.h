/**
  ******************************************************************************
  * @file   BetaFit_OLED_Module.h
  * @author Juan Morales Sáez (j.msaez@alumnos.upm.es)
  * @brief  OLED Module header.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the OLED module.
  ******************************************************************************
*/

#ifndef __BetaFit_OLED_Module_h
#define __BetaFit_OLED_Module_h

  /* Includes ------------------------------------------------------------------*/
  #include <Arduino.h>
  #include <SPI.h>
  #include <Wire.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>

  #include "BetaFit_Defintions.h"

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
  extern void OLED_Device_Begin (void);

  extern void OLED_Device_PowerOff (void);
  extern void OLED_Device_PowerOn  (void);

  extern void OLED_Device_Diplay_Menu_Item   (uint8_t muenu_item_id);
  extern void OLED_Device_Diplay_Clock       (uint8_t hour, uint8_t minutes);
  extern void OLED_Device_Diplay_Steps       (int step_number);
  extern void OLED_Device_Diplay_BodyHeat    (float body_heat);
  extern void OLED_Device_Diplay_HeartRate   (uint16_t heart_rate);

#endif // __BetaFit_OLED_Module_h
