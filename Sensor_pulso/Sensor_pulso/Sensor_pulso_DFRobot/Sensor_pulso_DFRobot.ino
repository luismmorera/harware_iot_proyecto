/***
 * Módulo sensor de pulso para el reloj inteligente Bfit.
 * La principal modificación realizada con respecto al código de internet es la de 
 * utilizar únicamente el sensor de pulos. Se va a buscar la optimización del uso
 * de la batería. 
 * Developed by: MRT and the team.
 * December 2022.
 */

#include <DFRobot_MAX30102.h>

DFRobot_MAX30102 pulseSensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  while(!pulseSensor.begin()){
    Serial.println("Pulse Sensor not found");
    delay(1000);
  }
  pulseSensor.sensorConfiguration(/*ledBrightness=*/ 0x1F, /*sampleAverage=*/SAMPLEAVG_4, \
                                  /*ledMode=*/MODE_MULTILED, /*sampleRate=*/SAMPLERATE_400, \
                                  /*pulseWidth=*/PULSEWIDTH_411, /*adcRange=*/ADCRANGE_4096);
    )
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("R=");
  Serial.print(pulseSensor.getRed());

  Serial.print("IR=");
  Serial.print(pulseSensor.getIR());
  delay(100);
}
