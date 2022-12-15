/**
  ******************************************************************************
  * @file   RTC.h
  * @author Mario López Parejo (mario.lopezp@alumnos.upm.es)
  * @brief  RTC Module header.
  *         
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         
  ******************************************************************************
*/
#ifndef __RTC_h
#define __RTC_h

  /* Includes ------------------------------------------------------------------*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "BetaFit_I2C_Module.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include "wifiConnection.h"

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
  

/*
* @brief    Función que se encarga de conectarse al servidor NTP y actualizar la hora del 
*           RTC según la información obtenida del NTP.
*
* @retval   true si se ha realizado la actualización de hora de forma correcta, false
*           en caso contrario.
*/
bool init_RTC();

/*
* @brief    Función que accede al registro del RTC y devuelve el año.
*/
uint16_t get_Year();

/*
* @brief    Función que accede al registro del RTC y devuelve el mes.
*/
uint8_t get_Month();

/*
* @brief    Función que accede al registro del RTC y devuelve el dia de mes.
*           La función de la librería que devuelve el día de la semana no se emplea al no ser necesario.
*/
uint8_t get_Day();

/*
* @brief    Función que accede al registro del RTC y devuelve la hora actual.
*/
uint8_t get_Hours();

/*
* @brief    Función que accede al registro del RTC y devuelve los minutos.
*/
uint8_t get_Minutes();

/*
* @brief    Función que accede al registro del RTC y devuelve los segundos.
*/
uint8_t get_Seconds();

#endif 
