/**
  ******************************************************************************
  * @file   buttonHandler.cpp
  * @author Pablo San Millán Fierro (pablo.sanmillanf@alumnos.upm.es)
  * @brief  Button interrupts handler.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the button interrupts, filters the bounces and 
  *         detects if is a short or long pulse.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "buttonHandler.h" // Module header

// BetaFit Libraries
#include "../BetaFit_Hardware.h"

/* Public variables-----------------------------------------------------------*/
bool BUTTON_SHORT_PULSE_FLAG;
bool BUTTON_LONG_PULSE_FLAG;

/* Private typedef -----------------------------------------------------------*/
#define DEBOUNCE_TIME_MS  50
#define LONG_PULSE_MS     700

#define BUTTON_PIN D6_PIN

enum BUTTON_STATE {IDLE_STATE, FALLING_EDGE, DEBOUNCED, SHORT_PULSE, LONG_PULSE};

/* Private variables----------------------------------------------------------*/
static bool pulse_detected;

/* Function prototypes -------------------------------------------------------*/
ICACHE_RAM_ATTR void buttonInterruptRoutine();
/* Functions -----------------------------------------------------------------*/
/**
 * Enables the button pin interrupts and initialize the module.
 *
 */
void buttonStart(){
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonInterruptRoutine, CHANGE);
  pulse_detected = false;
}


/**
 * State machine that filters the button bounces and detects if is a short or long pulse.
 * It should be called in every loop cycle.
 *
 */
void buttonStateMachine(){
  static BUTTON_STATE state;
  static long ms;
  switch(state){
    case IDLE_STATE:
      if(pulse_detected){
        state = FALLING_EDGE;
        ms = millis();
        #ifdef __buttonHandler_Debug_Mode
          Serial.println("Flanco de bajada detectado");
        #endif
      }
      break;
    case FALLING_EDGE:
      if(ms + DEBOUNCE_TIME_MS <= millis()){
        ms = millis();
        state = DEBOUNCED;
      }
      break;
    case DEBOUNCED:
      if(digitalRead(BUTTON_PIN)){
        state = IDLE_STATE;
      }
      else{
        state = SHORT_PULSE;
      }
      pulse_detected = false;
      break;
    case SHORT_PULSE:
      if(pulse_detected == true && (digitalRead(BUTTON_PIN))){
        state = IDLE_STATE;
        #ifdef __buttonHandler_Debug_Mode
          Serial.println("Pulsacion corta");
        #endif
        BUTTON_SHORT_PULSE_FLAG = true;
      }
      else if(ms + LONG_PULSE_MS <= millis()){
        ms = millis();
        state = LONG_PULSE;
        #ifdef __buttonHandler_Debug_Mode
          Serial.println("Pulsacion larga");
        #endif
        BUTTON_LONG_PULSE_FLAG = true;
      }
      break;
    case LONG_PULSE:
      if(pulse_detected == true && (digitalRead(BUTTON_PIN))){
        state = IDLE_STATE;
        pulse_detected = false;
      }
      break;
  }
}


/**************************************************/
/****************AUXILIAR FUNCTIONS****************/
/**************************************************/
/**
 * The ISR to detect button pulses.
 *
 */
ICACHE_RAM_ATTR void buttonInterruptRoutine(){
  pulse_detected = true;
}