/**
  ******************************************************************************
  * @file   BetaFit_SetpDetector_Module.h
  * @author Juan Morales Sáez (j.msaez@alumnos.upm.es)
  * @brief  Step Detector Module header.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the step detection.
  ******************************************************************************
*/

#ifndef __BetaFit_SetpDetector_Module_h
#define __BetaFit_SetpDetector_Module_h

#define __BetaFit_SetpDetector_Module_Debug_Mode

  /* Includes ------------------------------------------------------------------*/
  #include <Arduino.h>

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  #define Step_Detection_Default_Sensitivity 20

  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
  extern void beginSetpDetector (void);

  extern void storageAccelerationData (float AccelerationDataRegister[3]);

  extern uint16_t getStepCount (void);

#endif // __BetaFit_SetpDetector_Module_h
