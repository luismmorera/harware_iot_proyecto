/**
  ******************************************************************************
  * @file   webServer.cpp
  * @author Pablo San Millán Fierro (pablo.sanmillanf@alumnos.upm.es)
  *			Héctor García Palencia (hector.garpalencia@alumnos.upm.es)
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

#include "../jsonManager/jsonManager.h"
#include "../flash/flash.h"

/* Private typedef -----------------------------------------------------------*/
//Cookies
#define USER_COOKIE         "CONNECTED" 
#define DISCONNECT_COOKIE   "DISCONNECTED"
#define COOKIE_TTL_SECS     "300"
//Web or App
#define WEB_INTERFACE		0
#define APP_INTERFACE		1
/* Private variables----------------------------------------------------------*/
ESP8266WebServer webServer(80);

/* Function prototypes -------------------------------------------------------*/
static bool isExistingPath(String path);
static void notFoundHandler();
static bool isAuthenticated();
static void sendPageWithAuthentication(String data, String type);
static void sendResourceWithAuthentication(String data, String type);
static bool checkLogout(int webOrApp);
static void login(int webOrApp);
static void manageFormCredentials();
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  flashBegin();
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
  if(path == "/web" || path == "/web/" || path == "/web/index.html" || path == "/web/index" ){
    login(WEB_INTERFACE);
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
      manageFormCredentials();
      manageFormGeneralSettings();
    }
    sendPageWithAuthentication(readFile("/web/generalsettings.html"), "text/html");
  }
  
  //---------------------//
  //------Resources------//
  //---------------------//
  else if(path == "/web/dashboard.js" ){
    sendResourceWithAuthentication(readFile("/web/dashboard.js"), "application/javascript");
  }
  else if(path == "/web/dashboard.css"){
    sendResourceWithAuthentication(readFile("/web/dashboard.css"), "text/css");
  }
  else if(path == "/data/measurements" || path == "/app/measurements"){
	Serial.println("ENTRO RECURSO MEASUREMENT");
    sendResourceWithAuthentication(readFile("/data/measurements.json"), "application/json");
  }
  else if(path == "/data/usersettings"){
    sendResourceWithAuthentication(readFile("/data/usersettings.json"), "application/json");
  }
  else if(path == "/data/generalsettings"){
    sendResourceWithAuthentication(readFile("/data/generalsettings.json"), "application/json");
  }
  
  //-------------------------//
  //------APP Responses------//
  //-------------------------//
  else if(path == "/app/login"){
	  login(APP_INTERFACE);
  }
  else if(path == "/app/dashboard"){
	if(isAuthenticated()){
      manageFormCredentials();
    }
    else
      webServer.send(401);
  }
  else if(path == "/app/password"){
    if(isAuthenticated()){
      manageFormCredentials();
    }
    else
      webServer.send(401);
  }
  else if(path == "/app/usersettings"){
    if(isAuthenticated()){
      manageFormUserSettings();
    }
    else
      webServer.send(401);
  }
  else if(path == "/app/generalsettings"){
    if(isAuthenticated()){
      manageFormGeneralSettings();
    }
    else
      webServer.send(401);
  }
  else if(path == "/app/logout"){
    if(isAuthenticated()){
      checkLogout(APP_INTERFACE);
    }
    else
      webServer.send(401);
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
    String cookie = webServer.header("Cookie");
    
#ifdef DEBUG
    Serial.print("Found cookie: ");
    Serial.println(cookie);
#endif

    if (/*(cookie.indexOf("ESPSESSIONID=" USER_COOKIE) != -1)||*/(cookie.indexOf("ESPSESSIONID=\""USER_COOKIE"\"") != -1)) {
#ifdef DEBUG
      Serial.println("Authentication Successful");
#endif
      return true;
    }
  }
#ifdef DEBUG
  Serial.println("Authentication Failed");
#endif
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
    if(!checkLogout(WEB_INTERFACE)){
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
	Serial.println("ENTRO RECURSO AUTENTICADO");
    webServer.send(200, type, data);
  }
  else{
	Serial.println("NO ENTRO RECURSO AUTENTICADO");
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
static bool checkLogout(int webOrApp){
  if(webServer.method() == HTTP_POST){
    if (webServer.hasArg("logout")) {
#ifdef DEBUG
      Serial.println("LOG OUT");
#endif
	  if(webOrApp == WEB_INTERFACE){
		webServer.sendHeader("Location", "/web");
	  }
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
static void login(int webOrApp){
  if (webServer.method() == HTTP_POST){
    if (webServer.hasArg("uname") && webServer.hasArg("psw")) {
      if (compareCredentials(webServer.arg("uname"), webServer.arg("psw"))) {
		if(webOrApp == WEB_INTERFACE){
			webServer.sendHeader("Location", "/web/dashboard");
		}
        webServer.sendHeader("Cache-Control", "no-cache");
        webServer.sendHeader("Set-Cookie", "ESPSESSIONID=\"" USER_COOKIE "\"; Max-Age=" COOKIE_TTL_SECS "; Path=/");
        webServer.send(301);
        return;
      }
    }
  }
  webServer.send(200, "text/html", readFile("/web/index.html"));
}


/**
 * Handler asociated to the HTTP general settings page. 
 * Manage the fields related to the credentials change.
 *
 */
static void manageFormCredentials(){
  if(webServer.method() == HTTP_POST){
    if (webServer.hasArg("usr") && webServer.hasArg("psw")) {
      setCredentials(webServer.arg("usr"), webServer.arg("psw"));
    }
  }
}


/**
 * Handler asociated to the HTTP general settings page. 
 * Manage the fields related to the alarms.
 *
 */
static void manageFormGeneralSettings(){
  if(webServer.method() == HTTP_POST){
    if (webServer.hasArg("temperatura") && webServer.hasArg("frecuencia")) {
      setGeneralSettings(webServer.arg("temperatura"), webServer.arg("frecuencia"));
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
      
      setUserSettings(webServer.arg("nombre"), 
                      webServer.arg("apellido1"), 
                      webServer.arg("apellido2"), 
                      webServer.arg("altura"), 
                      webServer.arg("peso"));
    }
  }
}