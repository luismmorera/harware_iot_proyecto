#include "BetaFit_I2C_Module.h"

#define SLAVE_ADDR 0x3A

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Inicialización de los recursos I2C");

  I2C_Device_Begin();
}

void loop() {

  I2C_Device_Detected(0x3A);
  delay(5000);

}