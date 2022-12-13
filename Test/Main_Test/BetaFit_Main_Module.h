/**
  ******************************************************************************
  * @file   BetaFit_Main_Module.h
  * @author Juan Morales Sáez (j.msaez@alumnos.upm.es)
  * @brief  Mian Module header.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module is the main module of the BetaFit Project.
  ******************************************************************************
*/
#ifndef __BetaFit_Main_Module_h
#define __BetaFit_Main_Module_h

  /* Includes ------------------------------------------------------------------*/
  #include <Arduino.h>

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
   
   /**
    * @brief This function configure all the modules's resources.
    *
    * @retval none.
    */
    extern void BetaFit_Setup (void);

   /**
    * @brief This function execute tyhe main function of the BetaFit.
    *
    * @retval none.
    */
    extern void BetaFit_Main (void);

#endif // __BetaFit_Main_Module_h