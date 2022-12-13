#include "BetaFit_Definitions.h"

#include "BetaFit_Temperature_Sensor_Module.h"
#include "BetaFit_OLED_Module.h"

void setup() {

  Serial.begin(115200);

  OLED_Device_Begin();
}

void loop() {

  OLED_Device_Display_Measurement_Request(BETAFIT_MODE_BH);

  delay(2000);
  
  // Show in the display measuring process info.
  OLED_Device_Display_Measurement_Processing(BETAFIT_MODE_BH);

  delay(1000);

  // Turn temperature sensor on.
  Temperature_Sensor_WakeUp();

  // Get the measure and represent it in the display.

  float temperature = Get_Temperature_Celsius();

  Serial.print("Temperatura: "); Serial.print(temperature); Serial.print("\r\n");

  OLED_Device_Diplay_BodyHeat(temperature);

  // Turn temperature sensor off.
  Temperature_Sensor_Sleep();

  delay(1000);
}
