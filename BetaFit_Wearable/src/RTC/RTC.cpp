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
    
  uint8_t buff_hora[] = {to_BCD(second(epoch_time)), to_BCD(minute(epoch_time)), to_BCD(hour(epoch_time) + 1)};
  uint8_t buff_fecha[] = {to_BCD(day(epoch_time)), to_BCD(month(epoch_time)), to_BCD(year(epoch_time) -208)}; //-208
  
  #ifdef __BetaFit_RTC_Module_Debug_Mode
	Serial.println("Epoch");

	for (int i = 0; i<3; i++){
		Serial.println(buff_hora[i]);
	}
	for (int j = 0; j<3; j++){
		Serial.println(buff_fecha[j]);
	}
  #endif
  
  I2C_Device_Send_Data(SLAVE_ADDR_RTC,SECONDS_REGISTER, buff_hora, sizeof(buff_hora));
  I2C_Device_Send_Data(SLAVE_ADDR_RTC,DATE_REGISTER, buff_fecha, sizeof(buff_fecha));  

  // Turn off WiFi interface.
  wifiConnectionStop( );

	return update_done;
}

uint16_t get_Year(){
  byte anio[1] = {0};
  uint8_t unidades;
  uint8_t decenas;
  
  I2C_Device_Read_Data(SLAVE_ADDR_RTC, YEAR_REGISTER, anio, sizeof(anio));
  
  decenas = anio[0] >> 4;
  unidades = anio[0] & 0x0F;
  return (decenas*10 + unidades) + 2000;
}

//byte
uint8_t get_Month(){
  byte mes[1] = {0};
  uint8_t unidades;
  uint8_t decenas;
  
  I2C_Device_Read_Data(SLAVE_ADDR_RTC, MONTH_REGISTER, mes, sizeof(mes));
  
  decenas = mes[0] >> 4;
  unidades = mes[0] & 0x0F;
  return decenas*10 + unidades;
}

//byte
uint8_t get_Day(){
  byte dia[1] = {0};
  uint8_t unidades;
  uint8_t decenas;
  
  I2C_Device_Read_Data(SLAVE_ADDR_RTC, DATE_REGISTER, dia, sizeof(dia));
  
  decenas = (dia[0] >> 4) & 0x03;
  unidades = dia[0] & 0x0F;
  return decenas*10 + unidades;
}

//byte
uint8_t get_Hours(){
  byte horas[1] = {0};
  uint8_t unidades;
  uint8_t decenas;
  
  I2C_Device_Read_Data(SLAVE_ADDR_RTC, HOUR_REGISTER, horas, sizeof(horas));
  
  decenas = horas[0] >> 4;
  unidades = horas[0] & 0x0F;
  return decenas*10 + unidades;
}

//byte
uint8_t get_Minutes(){
  byte minuto[1] = {0};
  uint8_t unidades;
  uint8_t decenas;
  
  I2C_Device_Read_Data(SLAVE_ADDR_RTC, MINUTES_REGISTER, minuto, sizeof(minuto));
  
  decenas = minuto[0] >> 4;
  unidades = minuto[0] & 0x0F;
  return decenas*10 + unidades;
}

//byte
uint8_t get_Seconds(){
  byte segundo[1] = {0};
  uint8_t unidades;
  uint8_t decenas;
  
  I2C_Device_Read_Data(SLAVE_ADDR_RTC, SECONDS_REGISTER, segundo, sizeof(segundo));
  
  decenas = segundo[0] >> 4;
  unidades = segundo[0] & 0x0F;
  return decenas*10 + unidades;
}

uint8_t to_BCD(uint8_t valor){
  uint8_t unidades;
  uint8_t decenas;

  uint8_t valor_devuelto;
  
  decenas = valor / 10;

  if (decenas >= 1){
    unidades = valor - decenas*10;
  }else{
    unidades = valor;
  }
  
  #ifdef __BetaFit_RTC_Module_Debug_Mode
	Serial.println(decenas);
	Serial.print(unidades);
	Serial.println("");
  #endif
  
  valor_devuelto = (decenas << 4 | unidades);

  return valor_devuelto;
}