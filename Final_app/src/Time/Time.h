/**
  ******************************************************************************
  * @file   Time.h
  * @author Mario López Parejo (mario.lopezp@alumnos.upm.es)
  * @brief  Time Module header.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         
  ******************************************************************************
*/
#ifndef __Time_h
#define __Time_h

  /* Includes ------------------------------------------------------------------*/
  #include <NTPClient.h> 
  #include <WiFiUdp.h>

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/
  
  /*
   * Function that initialzes the time variables and starts the NTP Client
   */
  void init_ntp_client();
 
  /*
   * Function that updates the time variables asking the NTP server to send its actual time.
   */ 
  void get_hora_ntp();

  /*
   * Function that updates the time variables adding the seconds counted in the main program.
   * @param segundos_sumar: Contains the seconds to be added to the actual time.
   */ 
  void actualizar_hora(int segundos_sumar);
  
  /*
   * Function that updates the time variables adding the miliseconds counted in the main program.
   * @param milisegundos_sumar: Contains the milliseconds to be added to the actual time.
   */ 
  void actualizar_hora_ms(int milisegundos_sumar);  

  /*
   * Function that updates the time variables adding the seconds counted in the main program.
   * @param segundos_sumar: Contains the seconds to be added to the actual time.
   */ 
  void cambiar_hora(uint8_t hora, uint8_t minutos, uint8_t segundos);
  
  /*
   * Function that returns the actual time formatted in the following way:
   * hh:mm:ss
   */ 
  String get_time_hh_mm_ss ();

#endif 
