/**
  ******************************************************************************
  * @file   webServer.h
  * @author Pablo San Millán Fierro (pablo.sanmillanf@alumnos.upm.es)
  * @brief  HTTP web server.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the ESP8266 HTTP web server. 
  *         Based on ESP8266WebServer libray.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "webServer.h"             // Module header
#include <ESP8266WebServer.h>      // Servidor web

#define ARDUINOJSON_DECODE_UNICODE 1
#include <ArduinoJson.h>
#include "../flash/flash.h"

/* Private typedef -----------------------------------------------------------*/
//Cookies
#define USER_COOKIE         "CONNECTED" 
#define DISCONNECT_COOKIE   "DISCONNECTED"
#define COOKIE_TTL_SECS     "60"
/* Private variables----------------------------------------------------------*/
ESP8266WebServer webServer(80);

/* Function prototypes -------------------------------------------------------*/
static bool isExistingPath(String path);
static void notFoundHandler();
static bool isAuthenticated();
static void sendPageWithAuthentication(String data, String type);
static void sendResourceWithAuthentication(String data, String type);
static bool checkLogout();
static void login();
static void manageFormGeneralSettings();
static void manageFormUserSettings();

/* Functions -----------------------------------------------------------------*/
/**
 * Initializes the module. Called only once. 
 * This module should be called after "Serial.begin(baudrate)" instruction.
 * This module should be called after "flashBegin()" instruction.
 *
 */
void webServerBegin(){
  webServer.onNotFound([]() {                             // If the client requests any URI
    if (!isExistingPath(webServer.uri()))                 // send it if it exists
      notFoundHandler();                          // otherwise, respond with a 404 (Not Found) error
  });
  webServer.collectHeaders("Cookie");
  webServer.begin();
}


/**
 * Allow normal module working
 * Should calle in every loop cycle.
 *
 */
void webServerLoop(){
  webServer.handleClient();
}



/**************************************************/
/****************AUXILIAR FUNCTIONS****************/
/**************************************************/

/**
 * Check if the requested path exists and if so, invoke the asociated handler. 
 *
 * @param path The resource path.
 * @return true if the path exists.
 */
static bool isExistingPath(String path){
  //---------------------//
  //--------Pages--------//
  //---------------------//
  if(path == "/web" || path == "/web/" || path == "/web/index.html" || path == "/web/index"){
    login();
  }
  else if(path == "/web/dashboard.html" || path == "/web/dashboard"){
    sendPageWithAuthentication(readFile("/web/dashboard.html"), "text/html");
  }
  else if(path == "/web/usersettings.html" || path == "/web/usersettings"){
    if(isAuthenticated()){
      manageFormUserSettings();
    }
    sendPageWithAuthentication(readFile("/web/usersettings.html"), "text/html");
  }
  else if(path == "/web/generalsettings.html" || path == "/web/generalsettings"){
    if(isAuthenticated()){
      manageFormGeneralSettings();
    }
    sendPageWithAuthentication(readFile("/web/generalsettings.html"), "text/html");
  }
  
  //---------------------//
  //------Resources------//
  //---------------------//
  else if(path == "/web/dashboard.js"){
    sendResourceWithAuthentication(readFile("/web/dashboard.js"), "application/javascript");
  }
  else if(path == "/web/dashboard.css"){
    sendResourceWithAuthentication(readFile("/web/dashboard.css"), "text/css");
  }
  else if(path == "/data/measurements"){
    sendResourceWithAuthentication(readFile("/data/measurements.json"), "application/json");
  }
  else if(path == "/data/usersettings"){
    sendResourceWithAuthentication(readFile("/data/usersettings.json"), "application/json");
  }
  else if(path == "/data/generalsettings"){
    sendResourceWithAuthentication(readFile("/data/generalsettings.json"), "application/json");
  }
  else{
    return false;
  }
  return true;
}

/**
 * Handler for non-existing paths
 *
 */
static void notFoundHandler() {
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



/**
 * Check if the user is authenticated. 
 *
 * @return true if is authenticated.
 */
static bool isAuthenticated() {
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


/**
 * Check if the user is authenticated and if so, send the requested web page.
 * Also check if a logout request is received and if so, remove user credentials.
 *
 * @param data The data to be sended.
 * @param type Type of HTTP response. Should be "text/html".
 */
static void sendPageWithAuthentication(String data, String type){
  if(isAuthenticated()){
    if(!checkLogout()){
      webServer.send(200, type, data);
    }
  }
  else{
    webServer.sendHeader("Location", "/web");
    webServer.sendHeader("Cache-Control", "no-cache");
    webServer.send(301);
  }
}


/**
 * Check if the user is authenticated and if so, send the requested resource. 
 *
 * @param data The data to be sended.
 * @param type Type of HTTP response.
 */
static void sendResourceWithAuthentication(String data, String type){
  if(isAuthenticated()){
    webServer.send(200, type, data);
  }
  else{
    webServer.sendHeader("Location", "/web");
    webServer.sendHeader("Cache-Control", "no-cache");
    webServer.send(301);
  }
}



//-------------------------//
//------Page Handlers------//
//-------------------------//

/**
 * Check if a logout HTTP POST request is received.
 *
 * @return true if logout HTTP POST request is received.
 */
static bool checkLogout(){
  if(webServer.method() == HTTP_POST){
    if (webServer.hasArg("logout")) {
      Serial.println("LOG OUT");
      webServer.sendHeader("Location", "/web");
      webServer.sendHeader("Cache-Control", "no-cache");
      webServer.sendHeader("Set-Cookie", "ESPSESSIONID=" DISCONNECT_COOKIE "; Max-Age=" COOKIE_TTL_SECS "; Path=/");
      webServer.send(301);
      return true;
    }
  }
  return false;
}


/**
 * Handler asociated to the login page. If the credentials received are correct, 
 * allow the user to access to the system.
 *
 */
static void login(){
  if (webServer.method() == HTTP_POST){
    if (webServer.hasArg("uname") && webServer.hasArg("psw")) {
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, readFile("/data/credentials.json"));
      if (error) { 
        Serial.printf("Error occurred during JSON deserialization: %s\n", error.c_str());
        return; 
      }
      
      if (webServer.arg("uname") == doc["usr"] &&  webServer.arg("psw") == doc["psw"]) {
        webServer.sendHeader("Location", "/web/dashboard");
        webServer.sendHeader("Cache-Control", "no-cache");
        webServer.sendHeader("Set-Cookie", "ESPSESSIONID=" USER_COOKIE "; Max-Age=" COOKIE_TTL_SECS "; Path=/");
        webServer.send(301);
        return;
      }
    }
  }
  webServer.send(200, "text/html", readFile("/web/index.html"));
}


/**
 * Handler asociated to the HTTP general settings page. 
 * Manage the fields related to the credentials change and alarms.
 *
 */
static void manageFormGeneralSettings(){
  if(webServer.method() == HTTP_POST){
    if (webServer.hasArg("usr") && webServer.hasArg("psw")) {
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, readFile("/data/credentials.json"));
      if (error) { 
        Serial.printf("Error occurred during JSON deserialization: %s\n", error.c_str());
        return; 
      }
      doc["usr"] = webServer.arg("usr");
      doc["psw"] = webServer.arg("psw");
      
      String result;
      serializeJson(doc, result);
      writeFile("/data/credentials.json", result);
      Serial.println("\n");
      Serial.println(result);
      Serial.println("\n");
      Serial.println("Credentials Updated");
    }
    if (webServer.hasArg("temperatura") && webServer.hasArg("frecuencia")) {
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, readFile("/data/generalsettings.json"));
      if (error) { 
        Serial.printf("Error occurred during JSON deserialization: %s\n", error.c_str());
        return; 
      }
      doc["alarmas"]["temperatura"] = webServer.arg("temperatura");
      doc["alarmas"]["frecuenciacardiaca"] = webServer.arg("frecuencia");
      
      String result;
      serializeJson(doc, result);
      writeFile("/data/generalsettings.json", result);
      Serial.println("Alarm thresholds Updated");
    }
  }
}


/**
 * Handler asociated to the HTTP user settings page. 
 * Manage the fields related to the first name and lastnames and IMC.
 *
 */
static void manageFormUserSettings(){
  if(webServer.method() == HTTP_POST){
    if (webServer.hasArg("nombre") && webServer.hasArg("apellido1") &&  webServer.hasArg("apellido2")
                                   && webServer.hasArg("altura") && webServer.hasArg("peso")) {
      
      StaticJsonDocument<300> doc;
      DeserializationError error = deserializeJson(doc, readFile("/data/usersettings.json"));
      if (error) { 
        Serial.printf("Error occurred during JSON deserialization: %s\n", error.c_str());
        return; 
      }
      
      doc["ID"]["nombre"] = webServer.arg("nombre");
      doc["ID"]["apellido1"] = webServer.arg("apellido1");
      doc["ID"]["apellido2"] = webServer.arg("apellido2");
      doc["IMC"]["altura"] = webServer.arg("altura");
      doc["IMC"]["peso"] = webServer.arg("peso");
      
      String result;
      serializeJson(doc, result);
      writeFile("/data/usersettings.json", result);
      Serial.println("User Settings Updated");
    }
  }
}