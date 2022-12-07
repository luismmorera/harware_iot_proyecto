#include "src/wifiConnection/wifiConnection.h"


#ifndef STASSID
#define STASSID "ID-WIFI"
#define STAPSK  "PSW-WIFI"
#endif
void setup(void) {
  Serial.begin(9600);
  wifiConnectionBegin(STASSID, STAPSK);
}

static long ms;
bool activar = false;

void loop(void) {
  wifiConnectionLoop();

  
  if(ms + 30000 <= millis()){
    ms = millis();
    if(activar)
      wifiConnectionRestart(STASSID, STAPSK);
    else
      wifiConnectionStop();

    activar = !activar;
  }
}
