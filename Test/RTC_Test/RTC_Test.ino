#include "BetaFit_OLED_Module.h"

#include "BetaFit_Definitions.h"

#include "BetaFit_Accelerometer_Module.h"

#include "RTC.h"

uint8_t lastMinutes, currentMinutes, lastPosition;

void setup() {
  
  Serial.begin(9600);

  OLED_Device_Begin( );

  Accelerometer_Device_Begin( );

  init_RTC( );

  lastMinutes = 0; lastPosition = BETAFIT_OFF_POSITION;

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

    currentMinutes = get_Minutes();

    if(lastMinutes != currentMinutes){
      OLED_Device_Diplay_Clock(get_Hours(), currentMinutes);
    }
  }

  delay(50);

}
