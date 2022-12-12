#include "src/wifiConnection/wifiConnection.h"
#include "src/webServer/webServer.h"


#ifndef STASSID
#define STASSID "MOVISTAR_D157"
#define STAPSK  "mgD9KG23ju3jhPz7Y5F6"
#endif
void setup(void) {
  Serial.begin(9600);
  
  //Iniciamos el servidor para que pueda funcionar. 
  //Esto no implica encender el módulo WiFi por lo que se tiene que llamar en el setup()
  webServerBegin();
  
  //Encendemos módulo WiFi y intentamos establecer la conexión.
  //Solo se debe llamar a este método cuando se quiera conectarse a la WiFi.
  wifiConnectionStart(STASSID, STAPSK);
}

static long ms;
bool activar = false;

void loop(void) {
  
  //Si queremos que funcione el servidor, debemos llamar a este método en cada iteración
  //Necesita tener el WiFi encendido, si no no funciona
  webServerLoop();

  
  //Esto hace que cada 15 segundos se active o se desactive el WiFi
  if(ms + 15000 <= millis()){
    ms = millis();
    if(activar)
      wifiConnectionStart(STASSID, STAPSK);
    else
      wifiConnectionStop();

    activar = !activar;
  }
}


