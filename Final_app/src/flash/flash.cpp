/**
  ******************************************************************************
  * @file   flash.cpp
  * @author Pablo San Millán Fierro (pablo.sanmillanf@alumnos.upm.es)
  * @brief  Flash manager with SPI FFS.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the ESP8266 flash memory.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "flash.h"             // Module header
#include <FS.h>

/* Private typedef -----------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/
static bool initialized = false;
/* Function prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

/**
 * Initializes the module. Called only once. 
 * This function should be called after a "Serial.begin(baudrate)" instruction
 *
 */
void flashBegin(){
  if(!initialized){
    initialized = true;
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
        str += " -> ";
        str += dir.fileSize();
        str += " bytes\r\n";
    }
    
#ifdef DEBUG
    Serial.print(str);
#endif
  }
}

/**
 * Return the content of the file located in "path" or an empty string if the file doesn't exist. 
 *
 * @param path The file path.
 * @return content file or empty string if the file doesn't exist.
 */
String readFile(String path){
  String result = "";
  
  File file = SPIFFS.open(path, "r");
  if (!file) {
#ifdef DEBUG
    Serial.printf("Error opening file '%s' for reading", path);
#endif
    return "";
  }

#ifdef DEBUG
  Serial.printf("Reading file opened: %s\n", file.fullName());
#endif
  
  while(file.available()){
    result += file.readString();
  }
  file.close();
  return result;
}


/**
 * Write the String "text" in the file located in "path". 
 * If the file doesn't exist, is created.
 *
 * @param path The file path.
 * @param text The text to be written.
 * @return false if the file cannot be opened.
 */
bool writeFile(String path, String text){
  File file = SPIFFS.open(path, "w");
  
  if (!file) {
#ifdef DEBUG
    Serial.printf("Error opening file '%s' for writing", path);
#endif
    return false;
  }
  file.print(text);
  
#ifdef DEBUG
  Serial.printf("Writing file opened: %s\n", file.fullName());
#endif

  file.close();
  return true;
}
