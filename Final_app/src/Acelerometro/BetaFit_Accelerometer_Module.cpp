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

/* Private typedef -----------------------------------------------------------*/
#define X_THLD_VALUE_ON (0x01)
#define Y_THLD_VALUE_ON (0x04)
#define Z_THLD_VALUE_ON (0x04)

/* Private variables----------------------------------------------------------*/
Adafruit_MMA8451 accelerometer = Adafruit_MMA8451();

uint8_t DevicePostion;

/* Function prototypes -------------------------------------------------------*/
void Accelerometer_Device_Begin (void);

void Accelerometer_Get_Acceleration (float dataRegister[3]);

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

  DevicePostion = OFF_POSITION;

  accelerometer.setRange(MMA8451_RANGE_2_G);

  accelerometer.setDataRate(MMA8451_DATARATE_50_HZ);
}

/**
  * @brief  This function obtains the measurement taken by the accelerometer and 
  *         conditions the measurement according to the parameters with which the 
  *         device has been configured.
  *
  * @retval None
  */
void Accelerometer_Get_Acceleration (float dataRegister[3]) {
  
  // Get accelerometer data.
  sensors_event_t event; 
  accelerometer.getEvent(&event);

  dataRegister[0] = event.acceleration.x;
  dataRegister[1] = event.acceleration.y;
  dataRegister[2] = event.acceleration.z;

  #ifdef __BetaFit_Accelerometer_Module_Debug_Mode
    /* Display the results (acceleration is measured in m/s^2) */
    Serial.print("X: \t"); Serial.print(dataRegister[0]); Serial.print("\t");
    Serial.print("Y: \t"); Serial.print(dataRegister[1]); Serial.print("\t");
    Serial.print("Z: \t"); Serial.print(dataRegister[2]); Serial.print("\t");
    Serial.println("m/s^2 ");
  #endif

  // Determinate device position.
  if ((dataRegister[2] > Z_THLD_VALUE_ON || dataRegister[1] > Y_THLD_VALUE_ON) && (dataRegister[1] < Y_THLD_VALUE_ON)) DevicePostion = ON_POSITION;
  else DevicePostion = OFF_POSITION;
}

uint8_t Accelerometer_Get_Position (void) {
  
  #ifdef __BetaFit_Accelerometer_Module_Debug_Mode
    if (DevicePostion == ON_POSITION) Serial.println(F("User is looking at the device."));
    else Serial.println(F("User is NOT looking at the device."));
  #endif

  return DevicePostion;
}
