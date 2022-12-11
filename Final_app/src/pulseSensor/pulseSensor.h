/**
  ******************************************************************************
  * @file   Temperature_sensor.h
  * @author Mario López Parejo (mario.lopezp@alumnos.upm.es)
  * @brief  Temperature Sensor Module header.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         
  ******************************************************************************
*/
#ifndef __pulseSensor_h
#define __pulseSensor_h

  /* Includes ------------------------------------------------------------------*/
  #include "BetaFit_Hardware.h"

  /* Exported variables --------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/
  /* Exported macro ------------------------------------------------------------*/
  /* Exported Functions --------------------------------------------------------*/

/**
 *  Función de inicializacion de los recursos hardware y las variables de controlo que necesita el módulo para funcionar.
 *  Cada vez que queramos realizar una medida debemos ejecutar esta función, para resetear todos los valores de las variables internas 
 *  y para encender el pin de alimentación que se va a emplear.
 *  @Params:
 *    pin_alimentacion : pin digital que se utilizará para alimentar el sensor de pulso. De esta forma se puede apagar de forma sencilla y rapida.
 *    init_medida : variable booleana que se utiliza para iniciar la medida una vez se ha estabilizado el sensor de pulso y calculado la media.
 *    fin_medida : variable booleana que se activa cuando se han realizado los 20 segundos de medida.
 *    fin_transitorio : variable booleana que permite iniciar el calculo de la media una vez se ha activado la función de callback del contador de los 5 primeros segundos.
 */
void init_hr_sensor(int pin_alimentacion, bool init_medida, bool fin_medida, bool fin_transitorio);

/**@Params :  fin_transitorio : variable de control que se activa cuando el timer de 5 s termina
 *            init_medida : variable de control que se activa cuando el timer de 10 s termina
 *            fin_medida : variable de control que se activa cuando el timer de 30 s termina
 *     En resumen, los parámetros que se le pasan a esta funciona que se encarga de realizar la medida 
 *     son relacionados a las temporizaciones que se cumplen en el programa principal, que es desde donde se está ejecutando está función de manera periódica.
 *            
 * @returns : 1 si se ha producido un error en la medida -> Pulsaciones < 40 || pulsaciones > 200
 *          : -1 si se está produciendo la medida
 *          : el valor correspondiente si la medida es correcta.
 */
int realizar_medidas(bool init_medida, bool fin_medida, bool fin_transitorio);

/**
 * Función que apaga el sensor de pulso deshabilitando el pin que lo alimenta para que no consuma energía.
 * Cada vez que haya finalizado una medida debemos utilizar esta función para apagar el pin de alimentación.
 * @params : pin_alimentación a apagar
 */
void switch_off_hr_sensor(int pin_alimentacion);

/*
void deshabilitarMedida(bool fin_medida);

void iniciar_Medida(bool init_medida);

void avisar_fin_transitorio(bool fin_transitorio);
*/
#endif
