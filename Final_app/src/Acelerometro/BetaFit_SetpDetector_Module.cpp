/**
  ******************************************************************************
  * @file   BetaFit_SetpDetector_Module.c
  * @author Juan Morales Sáez (j.msaez@alumnos.upm.es)
  * @brief  Step Detector Module.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the step detection.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "BetaFit_SetpDetector_Module.h" // Module header

/* Private typedef -----------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/
uint16_t stepCount;

uint8_t AverageRegisterIndex, DetectionPeriodCounter, StepDetectionSensitivity;

float DeviationValue;

float AverageDataRegister[10];

/* Function prototypes -------------------------------------------------------*/
void beginSetpDetector (void);

void storageAccelerationData (float AccelerationDataRegister[3]);

void processStepDetectors (void);

void setSensitivity (uint8_t sensitivity);

uint16_t getStepCount (void);

void resetStepCount (void);

/* Functions -----------------------------------------------------------------*/

/**
* @brief  This function initializes the resources necessary for control and 
*         communication with the OLED module.
*
* @retval None
*/
void beginSetpDetector (void) {

  stepCount = 0; AverageRegisterIndex = 0; DetectionPeriodCounter = 0;

  StepDetectionSensitivity = Step_Detection_Default_Sensitivity;

  DeviationValue = 0.0;
}

void storageAccelerationData (float AccelerationDataRegister[3]) {

  float ActualAccelerationData = 0, PreviousAverage = 0;

  ActualAccelerationData = abs(AccelerationDataRegister[0]) + abs(AccelerationDataRegister[1]) + abs(AccelerationDataRegister[2]);

  // Calculate previous average.
  for (uint8_t i = 0; i < 10; i++)  PreviousAverage += AverageDataRegister[i];

  PreviousAverage = PreviousAverage / 10;
  
  // Storage actual average.
  AverageDataRegister[AverageRegisterIndex] = (ActualAccelerationData + PreviousAverage) / 2;

  if (AverageRegisterIndex < 10) AverageRegisterIndex = AverageRegisterIndex + 1;
  else AverageRegisterIndex = 0;

  DeviationValue += abs(ActualAccelerationData - PreviousAverage);

  if (DetectionPeriodCounter == 20) {
    
    processStepDetectors();

    DetectionPeriodCounter = 0;
    DeviationValue = 0;
  }

  else DetectionPeriodCounter = DetectionPeriodCounter + 1;
}

/**
  * @brief  This function obtains the measurement taken by the accelerometer and 
  *         conditions the measurement according to the parameters with which the 
  *         device has been configured.
  *
  * @retval None
  */
void processStepDetectors (void) {

  if(DeviationValue > StepDetectionSensitivity) stepCount  = stepCount + 1;

}

uint16_t getStepCount (void) {
  return stepCount;
}

void resetStepCount (void) {
  stepCount = 0;
}