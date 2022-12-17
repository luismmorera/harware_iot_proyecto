/**
  ******************************************************************************
  * @file   Time.c
  * @author Mario López Parejo (mario.lopezp@alumnos.upm.es)
  * @brief  Time Module. It access the NTP server and updates the time with a 
  * function to handle waking up from deep sleep mode.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "RTC.h" // Module header

// Impoorted Libraries
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>

// BetaFit Libraries
#include "../I2C/BetaFit_I2C_Module.h"
#include "../wifiConnection/wifiConnection.h"

/* Private typedef -----------------------------------------------------------*/

#define SLAVE_ADDR_RTC      0x68
#define SECONDS_REGISTER    0x00
#define MINUTES_REGISTER    0x01
#define HOUR_REGISTER       0x02
#define DATE_REGISTER       0x04
#define MONTH_REGISTER      0x05
#define YEAR_REGISTER       0x06

/* Private variables----------------------------------------------------------*/

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

/* Function prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

bool RTC_Device_Begin (const char *ssid, const char *password) {
	bool update_done = false;

  I2C_Device_Begin( );
  
  // Turn on WiFi interface.
  wifiConnectionStart(ssid, password);

	timeClient.begin();
	
  delay(10);

	update_done = timeClient.update();

  int epoch_time = timeClient.getEpochTime();
    
  uint8_t buff_hora[] = {(uint8_t)second(epoch_time), (uint8_t)minute(epoch_time), (uint8_t)hour(epoch_time) + 1};
  uint8_t buff_fecha[] = {(uint8_t)day(epoch_time), (uint8_t)month(epoch_time), (uint8_t)year(epoch_time)-208};
  
  #ifdef __BetaFit_RTC_Module_Debug_Mode
    Serial.println("Epoch");
  #endif
  
  I2C_Device_Send_Data(SLAVE_ADDR_RTC,SECONDS_REGISTER, buff_hora, sizeof(buff_hora));
  I2C_Device_Send_Data(SLAVE_ADDR_RTC,DATE_REGISTER, buff_fecha, sizeof(buff_fecha));  

  // Turn off WiFi interface.
  wifiConnectionStop( );

	return update_done;
}

uint16_t get_Year(){
  uint8_t anio[1] = {0};

  I2C_Device_Read_Data(SLAVE_ADDR_RTC, YEAR_REGISTER, anio, sizeof(anio));
  
  return anio[0] + 2000;
}

//byte
uint8_t get_Month(){
  uint8_t mes[1] = {0};

  I2C_Device_Read_Data(SLAVE_ADDR_RTC, MONTH_REGISTER, mes, sizeof(mes));

  return mes[0];
}

//byte
uint8_t get_Day(){
  uint8_t dia[1] = {0};

  I2C_Device_Read_Data(SLAVE_ADDR_RTC, DATE_REGISTER, dia, sizeof(dia));

  return dia[0];
}

//byte
uint8_t get_Hours(){
  uint8_t horas[1] = {0};

  I2C_Device_Read_Data(SLAVE_ADDR_RTC, HOUR_REGISTER, horas, sizeof(horas));

  return horas[0];
}

//byte
uint8_t get_Minutes(){
  uint8_t minuto[1] = {0};

  I2C_Device_Read_Data(SLAVE_ADDR_RTC, MINUTES_REGISTER, minuto, sizeof(minuto));

  return minuto[0];
}

//byte
uint8_t get_Seconds(){
  uint8_t segundo[1] = {0};

  I2C_Device_Read_Data(SLAVE_ADDR_RTC, SECONDS_REGISTER, segundo, sizeof(segundo));
  
  return segundo[0];
}
