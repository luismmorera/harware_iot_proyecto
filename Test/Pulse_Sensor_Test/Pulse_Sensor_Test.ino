#include "BetaFit_Definitions.h"

#include "pulseSensor.h"
#include "BetaFit_OLED_Module.h"

void setup() {

  Serial.begin(115200);

  OLED_Device_Begin();

  init_hr_sensor( );
}

void loop() {

  OLED_Device_Display_Measurement_Request(BETAFIT_MODE_HR);

  delay(2000);
  
  // Show in the display measuring process info.
  OLED_Device_Display_Measurement_Processing(BETAFIT_MODE_HR);

  delay(1000);

  // Get the measure and represent it in the display.

  uint16_t HR = (uint16_t) realizar_medidas( );

  Serial.print("Ritmo Cardiaco: "); Serial.print(HR); Serial.print("\r\n");

  OLED_Device_Diplay_HeartRate(HR);

  delay(1000);
}