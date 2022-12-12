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
#include "RTC.h"             // Module header

/* Private typedef -----------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

DS3231 myRTC;

/* Function prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

bool init_RTC(){
	bool update_done = false;
	timeClient.begin();
	Wire.begin();
	delay(10);
	update_done = timeClient.update();
	myRTC.setClockMode(false); // False -> Modo 24 horas; True -> Modo 12 horas.
	/*
	* setEpoch se encarga de actualizar los registros de fecha y hora internos del RTC.
	*/
	myRTC.setEpoch(NTPClient.getEpochTime());
	return update_done;
}

//byte
uint16_t get_Year(){
	return myRTC.getYear();	
}

//byte
uint8_t get_Month(){
	return myRTC.getMonth();	
}

//byte
uint8_t get_Day(){
	return myRTC.getDate();
}

//byte
uint8_t get_Hours(){
	return myRTC.getHour() + 1;
}

//byte
uint8_t get_Minutes(){
	return myRTC.getMinute();	
}

//byte
uint8_t get_Seconds(){
	return myRTC.getSecond();	
}
