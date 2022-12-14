/**
  ******************************************************************************
  * @file   jsonManager.cpp
  * @author Pablo San Millán Fierro (pablo.sanmillanf@alumnos.upm.es)
  * @brief  JSON files manager.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the JSON files located in the ESP8266 flash memory.
  *         Based on ArduinoJson libray.
  ******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "jsonManager.h"             // Module header

#define ARDUINOJSON_DECODE_UNICODE 1
#include <ArduinoJson.h>
#include "../flash/flash.h"

/* Private typedef -----------------------------------------------------------*/
#define MEASUREMENT_JSON_SIZE 4096
/* Private variables----------------------------------------------------------*/
/* Function prototypes -------------------------------------------------------*/
static String fromMounthNumberToMounthString(uint8_t mounth);

/* Functions -----------------------------------------------------------------*/
/**
 * Sets heart rate measurement entry in the JSON measurements.json located in "/data/measurements.json"
 *
 * @param tiempo Time Stamp. Should be "YYYY-MM-DDTHH:MM:SS" format.
 * @param valor Heart rate value. A float two decimal number.
 * @param alarma If temperature exceds temperature alarm threshold.
 */
void setHeartRateEntry(String tiempo, float valor, bool alarma){
  DynamicJsonDocument doc(MEASUREMENT_JSON_SIZE);
  DeserializationError error = deserializeJson(doc, readFile("/data/measurements.json"));
  if (error) { 
#ifdef __jsonManager_Debug_Mode
    Serial.printf("Error occurred during JSON deserialization: %s\n", error.c_str());
#endif
    return; 
  }
  
  JsonObject entry = doc["frecuenciacardiaca"].createNestedObject();
  entry["tiempo"] = tiempo;
  entry["valor"] = ((int)(valor*100))/100.0;
  entry["alarma"] = alarma;
  
  String result;
  serializeJson(doc, result);
  writeFile("/data/measurements.json", result);
  
#ifdef __jsonManager_Debug_Mode
  Serial.println("New heart rate entry added");
#endif
}


/**
 * Sets temperature measurement entry in the JSON measurements.json located in "/data/measurements.json"
 *
 * @param tiempo Time Stamp. Should be "YYYY-MM-DDTHH:MM:SS" format.
 * @param valor Temperature value. A float two decimal number.
 * @param alarma If temperature exceds temperature alarm threshold.
 */
void setTemperatureEntry(String tiempo, float valor, bool alarma){
  DynamicJsonDocument doc(MEASUREMENT_JSON_SIZE);
  DeserializationError error = deserializeJson(doc, readFile("/data/measurements.json"));
  if (error) {
#ifdef __jsonManager_Debug_Mode
    Serial.printf("Error occurred during JSON deserialization: %s\n", error.c_str());
#endif
    return; 
  }
  
  JsonObject entry = doc["temperaturas"].createNestedObject();
  entry["tiempo"] = tiempo;
  entry["valor"] = ((int)(valor*100))/100.0;
  entry["alarma"] = alarma;
  
  String result;
  serializeJson(doc, result);
  writeFile("/data/measurements.json", result);
  
#ifdef __jsonManager_Debug_Mode
  Serial.println("New temperature entry added");
#endif
}


/**
 * Sets steps measurement entry in the JSON measurements.json located in "/data/measurements.json"
 * If the new entry is from another mounth, reset the register (the register only saves the entrys from the last mounth).
 * Don't handle mounth/day errors (a day greater than 31 will be adopted like a correct entry).
 *
 * @param mes Measurement mounth from 1 to 12.
 * @param dia Day of the mounth. From 1 to 31.
 * @param valor The number of steps in a day.
 */
void setStepsEntry(uint8_t mes, uint8_t dia, uint32_t valor){
  DynamicJsonDocument doc(MEASUREMENT_JSON_SIZE);
  DeserializationError error = deserializeJson(doc, readFile("/data/measurements.json"));
  if (error) { 
#ifdef __jsonManager_Debug_Mode
    Serial.printf("Error occurred during JSON deserialization: %s\n", error.c_str());
#endif
    return; 
  }
  
  //If new entry is from another mounth reset the register.
  if(!fromMounthNumberToMounthString(mes).equalsIgnoreCase(doc["mes"])){
    doc["mes"] = mes;
    doc["pasos"]["muestras"].clear();
  }
  
  JsonObject entry = doc["pasos"]["muestras"].createNestedObject();
  entry["dia"] = dia;
  entry["valor"] = valor;
  
  String result;
  serializeJson(doc, result);
  writeFile("/data/measurements.json", result);
  
#ifdef __jsonManager_Debug_Mode
  Serial.println("New steps entry added");
#endif
}


/**
 * Sets user credentials in the JSON credentials.json located in "/data/credentials.json"
 *
 * @param usr User name.
 * @param psw User password.
 */
void setCredentials(String usr, String psw){
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, readFile("/data/credentials.json"));
  if (error) { 
#ifdef __jsonManager_Debug_Mode
    Serial.printf("Error occurred during JSON deserialization: %s\n", error.c_str());
#endif
    return; 
  }
  doc["usr"] = usr;
  doc["psw"] = psw;
  
  String result;
  serializeJson(doc, result);
  writeFile("/data/credentials.json", result);
  
#ifdef __jsonManager_Debug_Mode
  Serial.println("Credentials Updated");
#endif
}


/**
 * Compare user credentials with the JSON credentials.json located in "/data/credentials.json"
 *
 * @param usr User name.
 * @param psw User password.
 * @return true if are equal.
 */
bool compareCredentials(String usr, String psw){
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, readFile("/data/credentials.json"));
  if (error) { 
#ifdef __jsonManager_Debug_Mode
    Serial.printf("Error occurred during JSON deserialization: %s\n", error.c_str());
#endif
    return false; 
  }
  return doc["usr"] == usr && doc["psw"] == psw;
}


/**
 * Sets general settings in the JSON generalsettings.json located in "/data/generalsettings.json"
 *
 * @param temperatura Temperature alarm threshold.
 * @param frecuencia Heart rate  alarm threshold.
 */
void setGeneralSettings(String temperatura, String frecuencia){
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, readFile("/data/generalsettings.json"));
  if (error) { 
#ifdef __jsonManager_Debug_Mode
    Serial.printf("Error occurred during JSON deserialization: %s\n", error.c_str());
#endif
    return; 
  }
  doc["alarmas"]["temperatura"] = temperatura;
  doc["alarmas"]["frecuenciacardiaca"] = frecuencia;
  
  String result;
  serializeJson(doc, result);
  writeFile("/data/generalsettings.json", result);
  
#ifdef __jsonManager_Debug_Mode
  Serial.println("Alarm thresholds Updated");
#endif
}


/**
 * Sets user settings in the JSON usersettings.json located in "/data/usersettings.json"
 *
 * @param nombre User's name
 * @param apellido1 User's first surname.
 * @param apellido2 User's second surname.
 * @param altura User's height.
 * @param peso User's weight.
 */
void setUserSettings(String nombre, String apellido1, String apellido2, String altura, String peso){
  StaticJsonDocument<300> doc;
  DeserializationError error = deserializeJson(doc, readFile("/data/usersettings.json"));
  if (error) { 
#ifdef __jsonManager_Debug_Mode
    Serial.printf("Error occurred during JSON deserialization: %s\n", error.c_str());
#endif
    return; 
  }
  
  doc["ID"]["nombre"] = nombre;
  doc["ID"]["apellido1"] = apellido1;
  doc["ID"]["apellido2"] = apellido2;
  doc["IMC"]["altura"] = altura;
  doc["IMC"]["peso"] = peso;
  
  String result;
  serializeJson(doc, result);
  writeFile("/data/usersettings.json", result);
  
#ifdef __jsonManager_Debug_Mode
  Serial.println("User Settings Updated");
#endif
  
}


/**
 * Gets user's name from the JSON usersettings.json located in "/data/usersettings.json"
 *
 * @return User's name
 */
String getUserName(){
  StaticJsonDocument<300> doc;
  DeserializationError error = deserializeJson(doc, readFile("/data/usersettings.json"));
  if (error) { 
#ifdef __jsonManager_Debug_Mode
    Serial.printf("Error occurred during JSON deserialization: %s\n", error.c_str());
#endif
    return " "; 
  }
  
  return doc["ID"]["nombre"];
}



/**
 * Gets user's IMC from the JSON usersettings.json located in "/data/usersettings.json"
 *
 * @return The calculated IMC.
 */
float getUserIMC(){
  StaticJsonDocument<300> doc;
  DeserializationError error = deserializeJson(doc, readFile("/data/usersettings.json"));
  if (error) { 
#ifdef __jsonManager_Debug_Mode
    Serial.printf("Error occurred during JSON deserialization: %s\n", error.c_str());
#endif
    return 0; 
  }

  return String(doc["IMC"]["peso"]).toFloat()/pow(String(doc["IMC"]["altura"]).toFloat(), 2);
}


/**
 * Compare temperature threshold with the JSON generalsettings.json located in "/data/generalsettings.json"
 *
 * @param temperature The temperature measured.
 * @return true if the temperature is greater than the threshold.
 */
bool compareTemperature(uint32_t temperature){
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, readFile("/data/generalsettings.json"));
  if (error) { 
#ifdef __jsonManager_Debug_Mode
    Serial.printf("Error occurred during JSON deserialization: %s\n", error.c_str());
#endif
    return false; 
  }
  return temperature >= String(doc["alarmas"]["temperatura"]).toInt();
}


/**
 * Compare heart rate threshold with the JSON generalsettings.json located in "/data/generalsettings.json"
 *
 * @param heartRate The heart rate measured.
 * @return true if  the heart rate is greater than the threshold.
 */
bool compareHeartRate(uint32_t heartRate){
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, readFile("/data/generalsettings.json"));
  if (error) { 
#ifdef __jsonManager_Debug_Mode
    Serial.printf("Error occurred during JSON deserialization: %s\n", error.c_str());
#endif
    return false; 
  }
  return heartRate >= String(doc["alarmas"]["frecuenciacardiaca"]).toInt();
}





/**************************************************/
/****************AUXILIAR FUNCTIONS****************/
/**************************************************/
static String fromMounthNumberToMounthString(uint8_t mounth){
  switch(mounth){
    case 1:
      return "Enero";
    case 2:
      return "Febrero";
    case 3:
      return "Marzo";
    case 4:
      return "Abril";
    case 5:
      return "Mayo";
    case 6:
      return "Junio";
    case 7:
      return "Julio";
    case 8:
      return "Agosto";
    case 9:
      return "Septiembre";
    case 10:
      return "Octubre";
    case 11:
      return "Noviembre";
    case 12:
      return "Diciembre";
    default:
      return "";
  }
}