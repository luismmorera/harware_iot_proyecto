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

    #include "../BetaFit_Debug_Options.h"
    
  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/

    /**
      * @brief  This function initializes the resources necessary for control and 
      *         communication with the OLED module.
      *
      * @retval None
      */
    extern void OLED_Device_Begin (void);

    /**
      * @brief  This function initializes send the correct command in order to
      *         power off the OLED module.
      *
      * @retval None
      */
    extern void OLED_Device_PowerOff (void);
    
    /**
      * @brief  This function initializes send the correct command in order to
      *         power on the OLED module.
      *
      * @retval None
      */
    extern void OLED_Device_PowerOn  (void);

    /**
      * @brief  This function sends to the OLED display the title and logo 
      *         corresponding to the working mode in which the program is 
      *         currently running.
      *
      * @param  (uint8_t) muenu_item_id:  Identifies the mode of work which
      *         icon is to be represented in the OLED display.
      *
      * @retval None
      */
    extern void OLED_Device_Diplay_Menu_Item (uint8_t muenu_item_id);
    
    /**
      * @brief  This function sends to the OLED display the title and the data
      *         corresponding to the 'Clock' working mode.
      *
      * @param  (uint8_t) hour: Value to be represented in the OLED display.
      * @param  (uint8_t) minutes: Value to be represented in the OLED display.
      *
      * @retval None
      */
    extern void OLED_Device_Diplay_Clock (uint8_t hour, uint8_t minutes);
    
    /**
      * @brief  This function sends to the OLED display the title and the data
      *         corresponding to the 'Steps' working mode.
      *
      * @param  (int) step_number: Value to be represented in the OLED display.
      *
      * @retval None
      */
    extern void OLED_Device_Diplay_Steps (int step_number);
    
    /**
      * @brief  This function sends to the OLED display the title and the data
      *         corresponding to the 'Body Heat' working mode.
      *
      * @param  (float) step_number: Value to be represented in the OLED display.
      *
      * @retval None
      */
    extern void OLED_Device_Diplay_BodyHeat (float body_heat);
    
    /**
      * @brief  This function sends to the OLED display the title and the data
      *         corresponding to the 'Heart Rate' working mode.
      *
      * @param  (uint16_t) heart_rate: Value to be represented in the OLED display.
      *
      * @retval None
      */
    extern void OLED_Device_Diplay_HeartRate (uint16_t heart_rate);

    /**
      * @brief  This function represent in the display the request meassage for a new measuring process.
      *
      * @param (uint8_t) Measurement_Type: type of measuring running (Body Heat or Heart Rate).
      *
      * @retval None
      */
    extern void OLED_Device_Display_Measurement_Request (uint8_t Measurement_Type);

    /**
      * @brief  This function represent in the display that a measuring process
      *         is running.
      *
      * @param (uint8_t) Measurement_Type: type of measuring running (Body Heat or Heart Rate).
      *
      * @retval None
      */
    extern void OLED_Device_Display_Measurement_Processing (uint8_t Measurement_Type);
    
    /**
      * @brief  This function represent in the information section of the display
      *         the wifi enabled icon and the IP asigned to the device.
      *
      * @param (String) IPdir: IP direcction of the device.
      *
      * @retval None
      */
    extern void OLED_Device_Display_Wifi_On (String IPdir);

    /**
      * @brief  This function represent in the information section of the display
      *         the wifi enabled icon and 'Conecting...' text.
      *
      * @retval None
      */
    extern void OLED_Device_Display_Wifi_Connecting (void);

    /**
      * @brief  This function represent in the information section of the display
      *         the wifi disabled icon.
      *
      * @retval None
      */
    extern void OLED_Device_Display_Wifi_Off (void);

#endif // __BetaFit_OLED_Module_h
