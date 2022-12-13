/**
  ******************************************************************************
  * @file   BetaFit_Main_Module.cpp
  * @author Juan Morales Sáez (j.msaez@alumnos.upm.es)
  * @brief  Mian Module.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module is the main module of the BetaFit Project.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "BetaFit_Main_Module.h" // Module header

#include "BetaFit_Definitions.h"

/* Private typedef -----------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

uint8_t BetaFit_Mode;

/* Function prototypes -------------------------------------------------------*/

void BetaFit_Setup (void);

void BetaFit_Main (void);

void BetaFit_Init_Mode_Main (void);

void BetaFit_Clock_Mode_Main (void);

void BetaFit_Steps_Mode_Main (void);

void BetaFit_Body_Heat_Mode_Main (void);

void BetaFit_Heart_Rate_Mode_Main (void);

void BetaFit_Configuration_Mode_Main (void);

/* Functions -----------------------------------------------------------------*/

/**
   * @brief This function configure all the modules's resources.
   * 
   * @retval none.
   */
void BetaFit_Setup (void) {

   BetaFit_Mode = 0x00;

}

/**
   * @brief This function execute tyhe main function of the BetaFit.
   *
   * @retval none.
   */
void BetaFit_Main (void) {

   switch (BetaFit_Mode) {

      case BETAFIT_MODE_INIT:
         BetaFit_Init_Mode_Main ( );
      break;

      case BETAFIT_MODE_CLOCK:
         BetaFit_Clock_Mode_Main ( );
      break;

      case BETAFIT_MODE_STEPS:
         BetaFit_Steps_Mode_Main ( );
      break;

      case BETAFIT_MODE_BH:
         BetaFit_Body_Heat_Mode_Main ( );
      break;

      case BETAFIT_MODE_HR:
         BetaFit_Heart_Rate_Mode_Main ( );
      break;

      case BETAFIT_MODE_CONF:
         BetaFit_Configuration_Mode_Main ( );
      break;

      default:
      break; 
   }

}

void BetaFit_Init_Mode_Main (void) {

}

void BetaFit_Clock_Mode_Main (void) {

}

void BetaFit_Steps_Mode_Main (void) {

}

void BetaFit_Body_Heat_Mode_Main (void) {

}

void BetaFit_Heart_Rate_Mode_Main (void) {

}

void BetaFit_Configuration_Mode_Main (void) {

}