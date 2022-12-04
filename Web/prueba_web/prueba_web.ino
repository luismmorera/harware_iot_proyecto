#include <ESP8266WiFi.h>        // biblioteca wifi de esp8266
#include <ESP8266WebServer.h>   // Servidor web
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FS.h>

#ifndef STASSID
#define STASSID "Redmi Note 11"
#define STAPSK  "Hd12345678"
#endif


const char *ssid = STASSID;
const char *password = STAPSK;

// Objecto servidor
ESP8266WebServer webServer(80);


void setup(void) {

  //Set wifi connection
  wifiConnect();

  //Configure HTTP server
  configure_WebServer();

  //Configure File System
  SPIFFS.begin();

  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  String str = "";
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
      str += dir.fileName();
      str += " / ";
      str += dir.fileSize();
      str += "\r\n";
  }
  Serial.print(str);
}


void loop(void) {
  webServer.handleClient();
}

/*
void write_in_flash(uint16_t mean){
  File file = SPIFFS.open("/log.txt", "a");
  
  if (!file) {
    Serial.println("Error opening file for writing");
    return;
  }
  file.print(timeClient.getFormattedTime() + " -> "
                                                  "Mean: " + String(mean) + ",\t"
                                                  "Alarm: " + ((mean >= light_sensor_threshold)  ? "ON" : "OFF") + "\n");
  file.close();
}

*/
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

void configure_WebServer () {
  webServer.on("/web", rootHandler);
  webServer.on("/web/dashboard.html", dashboardHandler);
  webServer.on("/web/dashboard.js", dashboardJSHandler);
  webServer.on("/web/dashboard.css", dashboardCSSHandler);
  webServer.on("/web/usersettings.html", userSettingsHandler);
  webServer.on("/web/generalsettings.html", generalSettingsHandler);
  webServer.on("/web/data", dataHandler);
  webServer.onNotFound(notFoundHandler);
  
  webServer.begin();
}


// Página inicial con el menú de opciones
void rootHandler() {
  
  sendPage("/web/index.html", "text/html");
}

void dashboardHandler(){
  sendPage("/web/dashboard.html", "text/html");
}

void dashboardJSHandler(){
  sendPage("/web/dashboard.js", "application/javascript");
}

void dashboardCSSHandler(){
  sendPage("/web/dashboard.css", "text/css");
}

void userSettingsHandler(){
  sendPage("/web/usersettings.html", "text/html");
}

void generalSettingsHandler(){
  sendPage("/web/generalsettings.html", "text/html");
}

void dataHandler(){
  File file = SPIFFS.open("/web/data_example.json", "r");
  size_t sent = webServer.streamFile(file, "application/json");
  file.close();
}

void sendPage(String url, String type){
  File file = SPIFFS.open(url, "r");
  Serial.println(file.fullName());
  size_t sent = webServer.streamFile(file, type);
  file.close();
}


void notFoundHandler() {
  String msg = "Página no encontrada\n\n";
  msg += "URI: ";
  msg += webServer.uri();
  msg += "\nMetodo: ";
  msg += (webServer.method() == HTTP_GET) ? "GET" : "POST";
  msg += "\nArgumentos: ";
  msg += webServer.args();
  msg += "\n";
  for (uint8_t i = 0; i < webServer.args(); i++) {
    msg += " " + webServer.argName(i) + ": " + webServer.arg(i) + "\n";
  }
  webServer.send(404, "text/plain", msg);
}
