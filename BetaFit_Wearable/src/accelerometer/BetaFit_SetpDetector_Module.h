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

  /* Includes ------------------------------------------------------------------*/
  #include <Arduino.h>

  #include "../BetaFit_Debug_Options.h"

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  #define BETAFIT_STEP_DETECTOR_DEFAULT_SENSITIVITY 20

  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
  extern void beginSetpDetector (void);

  extern void StepDetectorUpdateAccelerationData (float x_axis, float y_axis, float z_axis);

  extern uint16_t getStepCount (void);

  extern void resetStepCount (void);

#endif // __BetaFit_SetpDetector_Module_h
