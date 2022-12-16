/**
  ******************************************************************************
  * @file   BetaFit_Accelerometer_Module.c
  * @author Juan Morales Sáez (j.msaez@alumnos.upm.es)
  * @brief  Accelerometer Module.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the OLED module.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "BetaFit_Accelerometer_Module.h" // Module header

// Adafruit Libraries
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

// BetaFit Libraries
#include "../accelerometer/BetaFit_SetpDetector_Module.h"

/* Private typedef -----------------------------------------------------------*/
#define X_THLD_VALUE_ON 2
#define Y_THLD_VALUE_ON 4
#define Z_THLD_VALUE_ON 4

#define X_THLD_VALUE_MEAS_BH 1
#define Y_THLD_VALUE_MEAS_BH 8
#define Z_THLD_VALUE_MEAS_BH 2

/* Private variables----------------------------------------------------------*/
Adafruit_MMA8451 accelerometer = Adafruit_MMA8451();

uint8_t DevicePostion;

/* Function prototypes -------------------------------------------------------*/
void Accelerometer_Device_Begin (void);

void Accelerometer_Update_Acceleration_Data (void);

uint8_t Accelerometer_Get_Position (void);

/* Functions -----------------------------------------------------------------*/

/**
* @brief  This function initializes the resources necessary for control and 
*         communication with the OLED module.
*
* @retval None
*/
void Accelerometer_Device_Begin (void) {
  
  if (!accelerometer.begin()) {
    #ifdef __BetaFit_Accelerometer_Module_Debug_Mode
      Serial.println(F("MMA8451 allocation failed"));
    #endif
    for(;;); // Don't proceed, loop forever
  }

  #ifdef __BetaFit_Accelerometer_Module_Debug_Mode
    Serial.println(F("MMA8451 Accelerometer found!"));
  #endif

  DevicePostion = BETAFIT_OFF_POSITION;

  accelerometer.setRange(MMA8451_RANGE_2_G);

  accelerometer.setDataRate(MMA8451_DATARATE_50_HZ);

  beginSetpDetector( );
}

/**
  * @brief  This function obtains the measurement taken by the accelerometer and 
  *         conditions the measurement according to the parameters with which the 
  *         device has been configured.
  *
  * @retval None
  */
void Accelerometer_Update_Acceleration_Data (void) {
  
  float x_axis = 0, y_axis = 0, z_axis = 0;
  
  // Get accelerometer data.
  sensors_event_t event; 
  accelerometer.getEvent(&event);

  x_axis = event.acceleration.x;
  y_axis = event.acceleration.y;
  z_axis = event.acceleration.z;

  #ifdef __BetaFit_Accelerometer_Module_Debug_Mode
    /* Display the results (acceleration is measured in m/s^2) */
    Serial.print("X: \t"); Serial.print(x_axis); Serial.print("\t");
    Serial.print("Y: \t"); Serial.print(y_axis); Serial.print("\t");
    Serial.print("Z: \t"); Serial.print(z_axis); Serial.print("\t");
    Serial.println("m/s^2 ");
  #endif

  // Update acceleration data in the step detector.
  StepDetectorUpdateAccelerationData (x_axis, y_axis, z_axis);


  // Determinate device position.
  if (((z_axis > Z_THLD_VALUE_ON) || ((y_axis < - Y_THLD_VALUE_ON) && (y_axis > -8 ))) && ((x_axis < X_THLD_VALUE_ON) && (x_axis > - X_THLD_VALUE_ON))) {
    DevicePostion = BETAFIT_ON_POSITION;
  }
  
  else if ((y_axis < - Y_THLD_VALUE_MEAS_BH) && ((x_axis < X_THLD_VALUE_MEAS_BH) && (x_axis > - X_THLD_VALUE_MEAS_BH)) && ((z_axis < Z_THLD_VALUE_MEAS_BH) && (z_axis > - Z_THLD_VALUE_MEAS_BH))) {
    DevicePostion = BETAFIT_MEAS_BH_POSITION;
  }
  
  else {
    DevicePostion = BETAFIT_OFF_POSITION;
  }

}

uint8_t Accelerometer_Get_Position (void) {
  
  #ifdef __BetaFit_Accelerometer_Module_Debug_Mode
    if (DevicePostion == BETAFIT_ON_POSITION) Serial.println(F("User is looking at the device."));
    else Serial.println(F("User is NOT looking at the device."));
  #endif

  return DevicePostion;
}
