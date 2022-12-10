#include "BetaFit_Defintions.h"
#include "BetaFit_OLED_Module.h"

void setup() {
  Serial.begin(9600);

  OLED_Device_Begin();
}

void loop() {
  
  OLED_Device_Diplay_Menu_Item(BETAFIT_MODE_INIT);
  delay(1500);

  OLED_Device_Diplay_Menu_Item(BETAFIT_MODE_CLOCK);
  delay(1500);

  OLED_Device_Diplay_Menu_Item(BETAFIT_MODE_STEPS);
  delay(1500);

  OLED_Device_Diplay_Menu_Item(BETAFIT_MODE_BH);
  delay(1500);

  OLED_Device_Diplay_Menu_Item(BETAFIT_MODE_HR);
  delay(1500);

  OLED_Device_Diplay_Menu_Item(BETAFIT_MODE_CONF);
  delay(1500);

  OLED_Device_Diplay_Clock(23, 45);
  delay(1500);

  OLED_Device_Diplay_HeartRate (76);
  delay(1500);

  OLED_Device_Diplay_BodyHeat (34.5670);
  delay(1500);

  OLED_Device_Diplay_Steps (5);
  delay(1500);

  OLED_Device_Diplay_Steps (76);
  delay(1500);

  OLED_Device_Diplay_Steps (567);
  delay(1500);

  OLED_Device_Diplay_Steps (4367);
  delay(1500);

  OLED_Device_Diplay_Steps (99978);
  delay(1500);
}
