#include <ESP8266WiFi.h>        // biblioteca wifi de esp8266
#include <ESP8266WebServer.h>   // Servidor web
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FS.h>

#ifndef STASSID
#define STASSID "a"
#define STAPSK  "a"
#endif


const char *ssid = STASSID;
const char *password = STAPSK;

// Objecto servidor
ESP8266WebServer webServer(80);

//Cookies
#define USER_COOKIE  "CONNECTED" 
#define DISCONNECT_COOKIE  "DISCONNECTED"

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
  webServer.onNotFound([]() {                             // If the client requests any URI
    if (!isExistingPath(webServer.uri()))                 // send it if it exists
      notFoundHandler();                          // otherwise, respond with a 404 (Not Found) error
  });
  webServer.collectHeaders("Cookie");
  webServer.begin();
}


//Existings paths handler
bool isExistingPath(String path){
  if(path == "/web" || path == "/web/" || path == "/web/index.html" || path == "/web/index"){
    login();
  }
  else if(path == "/web/dashboard.html" || path == "/web/dashboard"){
    sendPageWithAuthentication("/web/dashboard.html", "text/html");
  }
  else if(path == "/web/dashboard.js"){
    sendPageWithAuthentication("/web/dashboard.js", "application/javascript");
  }
  else if(path == "/web/dashboard.css"){
    sendPageWithAuthentication("/web/dashboard.css", "text/css");
  }
  else if(path == "/web/usersettings.html" || path == "/web/usersettings"){
    sendPageWithAuthentication("/web/usersettings.html", "text/html");
  }
  else if(path == "/web/generalsettings.html" || path == "/web/generalsettings"){
    sendPageWithAuthentication("/web/generalsettings.html", "text/html");
  }
  else if(path == "/web/data"){
    sendPageWithAuthentication("/web/data_example.json", "application/json");
  }
  else{
    return false;
  }
  return true;
}


void sendPageWithAuthentication(String url, String type){
  if(isAuthenticated()){
    if(webServer.method() == HTTP_POST){
      if (webServer.hasArg("logout")) {
        Serial.println("LOG OUT");
        webServer.sendHeader("Location", "/web");
        webServer.sendHeader("Cache-Control", "no-cache");
        webServer.sendHeader("Set-Cookie", "ESPSESSIONID=" DISCONNECT_COOKIE "; Max-Age=60; Path=/web");
        webServer.send(301);
        return;
      }
    }
    sendPage(url, type);
  }
  else{
    webServer.sendHeader("Location", "/web");
    webServer.sendHeader("Cache-Control", "no-cache");
    webServer.send(301);
  }
}


void sendPage(String url, String type){
  File file = SPIFFS.open(url, "r");
  Serial.printf("File sent: %s\n", file.fullName());
  webServer.streamFile(file, type);
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

void login(){
  if (webServer.method() == HTTP_POST){
    if (webServer.hasArg("uname") && webServer.hasArg("psw")) {
      if (webServer.arg("uname") == "admin" &&  webServer.arg("psw") == "admin") {
        webServer.sendHeader("Location", "/web/dashboard");
        webServer.sendHeader("Cache-Control", "no-cache");
        webServer.sendHeader("Set-Cookie", "ESPSESSIONID=" USER_COOKIE "; Max-Age=60; Path=/web");
        webServer.send(301);
        return;
      }
    }
  }
  sendPage("/web/index.html", "text/html");
}

bool isAuthenticated() {
  if (webServer.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = webServer.header("Cookie");
    Serial.println(cookie);
    if (cookie.indexOf("ESPSESSIONID=" USER_COOKIE) != -1) {
      Serial.println("Authentication Successful");
      return true;
    }
  }
  Serial.println("Authentication Failed");
  return false;
}
