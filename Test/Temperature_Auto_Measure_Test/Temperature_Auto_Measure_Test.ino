#include "BetaFit_Hardware.h"

#include "BetaFit_OLED_Module.h"

#include "BetaFit_Definitions.h"

#include "BetaFit_Accelerometer_Module.h"

#include "BetaFit_Temperature_Sensor_Module.h"

uint8_t   lastPosition;
uint16_t  lastStepsValue, currentStepsValue;

void setup() {

  Serial.begin(9600);

  lastPosition = BETAFIT_OFF_POSITION;

  lastStepsValue = 0; currentStepsValue = 0;

  Accelerometer_Device_Begin( );

  OLED_Device_Begin( );

  Temperature_Sensor_Begin( );

  OLED_Device_Diplay_Menu_Item(BETAFIT_MODE_INIT);
  delay(1500);
}

void loop() {

  Accelerometer_Update_Acceleration_Data( );
 
  if(Accelerometer_Get_Position() == BETAFIT_ON_POSITION && lastPosition == BETAFIT_OFF_POSITION) {
    lastPosition = BETAFIT_ON_POSITION;
    OLED_Device_PowerOn();
  }

  if(Accelerometer_Get_Position() == BETAFIT_OFF_POSITION && lastPosition == BETAFIT_ON_POSITION) {
    lastPosition = BETAFIT_OFF_POSITION;
    OLED_Device_PowerOff();
  }

  if(Accelerometer_Get_Position() == BETAFIT_ON_POSITION){

    currentStepsValue = getStepCount();

    if(lastStepsValue != currentStepsValue){
      OLED_Device_Diplay_Steps (currentStepsValue);
    }
  }

  if (Accelerometer_Get_Position() == BETAFIT_MEAS_BH_POSITION) {
    
    delay(500);

    if (Accelerometer_Get_Position() == BETAFIT_MEAS_BH_POSITION) {
      
      OLED_Device_PowerOn();

      OLED_Device_Display_Measurement_Processing(BETAFIT_MODE_BH);

      // Turn temperature sensor on.
      Temperature_Sensor_WakeUp();

      delay(10);

      // Get the measure and represent it in the display.

      float temperature = Get_Temperature_Celsius();

      Serial.print("Temperatura: "); Serial.print(temperature); Serial.print("\r\n");

      OLED_Device_Diplay_BodyHeat(temperature);

      // Turn temperature sensor off.
      Temperature_Sensor_Sleep();

      delay(5000);
    }
  }

  delay(50);
}
