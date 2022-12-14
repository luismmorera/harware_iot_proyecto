/**
  ******************************************************************************
  * @file   buttonHandler.h
  * @author Pablo San Millán Fierro (pablo.sanmillanf@alumnos.upm.es)
  * @brief  Button interrupts handler.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the button interrupts, filters the bounces and 
  *         detects if is a short or long pulse.
  ******************************************************************************
*/
#ifndef __buttonHandler_h
#define __buttonHandler_h

  /* Includes ------------------------------------------------------------------*/
    #include <Arduino.h>

    #include "../BetaFit_Debug_Options.h"

  /* Exported variables --------------------------------------------------------*/
    extern bool BUTTON_SHORT_PULSE_FLAG;
    extern bool BUTTON_LONG_PULSE_FLAG;
  
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
    
    /**
      * @brief This function initialize button resources.
      *
      * @retval none.
      */
    extern void buttonStart (void);

    /**
      * @brief  This funtions runs the state machine that filters the button bounces 
      *         and detects if is a short or long pulse.
      *         It should be called in every loop cycle.
      *
      * @retval none.
      */
    extern void buttonStateMachine (void);

#endif // __buttonHandler_h