/**
  ******************************************************************************
  * @file   wifiConnection.cpp
  * @author Pablo San Millán Fierro (pablo.sanmillanf@alumnos.upm.es)
  * @brief  WiFi connection handler.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the ESP8266 WiFi connection and all the feautres 
  *         related to it: the web server. Based on ESP8266WiFi libray.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "wifiConnection.h"             // Module header
#include <ESP8266WiFi.h>      // WiFi



/* Private typedef -----------------------------------------------------------*/
/* Private variables----------------------------------------------------------*/
/* Function prototypes -------------------------------------------------------*/
static void wifiConnect(String ssid, String password);
/* Functions -----------------------------------------------------------------*/

/**
 * Switch on WiFi hardware to enable WiFi connections.
 *
 */
void wifiConnectionStart(String ssid, String password){
  WiFi.forceSleepWake();
#ifdef DEBUG
  Serial.println("Iniciando la reconexión");
#endif
  wifiConnect(ssid, password);
}


/**
 * Switch off WiFi hardware to reduce power consumption.
 *
 */
void wifiConnectionStop(){
  WiFi.mode( WIFI_OFF );
  WiFi.forceSleepBegin();
#ifdef DEBUG
  Serial.printf("Realizada la desconexión\n");
#endif
}



/**************************************************/
/****************AUXILIAR FUNCTIONS****************/
/**************************************************/
static void wifiConnect(String ssid, String password){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
#ifdef DEBUG
  Serial.print("Conectándo a la wifi con SSID");
  Serial.print(ssid);
  Serial.print(" y clave ");
  Serial.println(password);
#endif
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#ifdef DEBUG
    switch (WiFi.status()){
      case WL_NO_SSID_AVAIL:
        Serial.println("WL_NO_SSID_AVAIL");
        break;
      case WL_CONNECTED:
        Serial.println("WL_CONNECTED");
        break;
      case WL_CONNECT_FAILED:
        Serial.println("WL_CONNECT_FAILED");
        break;
      case WL_IDLE_STATUS:
        Serial.println("WL_IDLE_STATUS");
        break;
      case WL_DISCONNECTED:
        Serial.println("WL_DISCONNECTED");
        break;
    }
#endif
  }

#ifdef DEBUG
  Serial.println("\nConectado a WiFi!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
#endif
}