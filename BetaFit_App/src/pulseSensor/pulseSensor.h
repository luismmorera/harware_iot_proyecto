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
    #include <Arduino.h>

    #include "../BetaFit_Debug_Options.h"

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
    void init_hr_sensor(void);

    /**
      *  Función que consiste en un bucle que se ejecuta durante 30 segundos y realiza medidas cada 10 ms. Las medidas efectivas las realiza en los últimos 
      *  20 segundos. 
      *            
      * @returns : 1 si se ha producido un error en la medida -> Pulsaciones < 40 || pulsaciones > 200
      *          : el valor correspondiente si la medida es correcta.
      */
    uint8_t realizar_medidas(void);

#endif