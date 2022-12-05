
#include <ESP8266WiFi.h>        // biblioteca wifi de esp8266

#include "src/flash/flash.h"
#include "src/webServer/webServer.h"

#ifndef STASSID
#define STASSID "MOVISTAR_D157"
#define STAPSK  "mgD9KG23ju3jhPz7Y5F6"
#endif


const char *ssid = STASSID;
const char *password = STAPSK;

void setup(void) {

  //Set wifi connection
  wifiConnect();

  flashBegin();
  
  //Configure HTTP server
  webServerBegin();
}


void loop(void) {
  webServerLoop();
}

void wifiConnect(){
  Serial.begin(9600);
  
  // Da tiempo a que se inicialice el hardware de la Wifi
  delay(10);
   
  WiFi.begin(ssid, password);  
  Serial.printf("Conectándo a la wifi con SSID %s y clave %s",ssid,password );
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado a WiFi!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}
