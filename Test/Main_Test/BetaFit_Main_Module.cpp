/**
  ******************************************************************************
  * @file   BetaFit_Main_Module.cpp
  * @author Juan Morales Sáez (j.msaez@alumnos.upm.es)
  * @brief  Mian Module.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module is the main module of the BetaFit Project.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "BetaFit_Main_Module.h" // Module header

#include "BetaFit_Definitions.h"

#include "BetaFit_Accelerometer_Module.h"
#include "BetaFit_SetpDetector_Module.h"
#include "BetaFit_Temperature_Sensor_Module.h"
#include "BetaFit_OLED_Module.h"

/* Private typedef -----------------------------------------------------------*/
#define BetaFit_Main_Module_ConfigModeStatus_Active   0xFF
#define BetaFit_Main_Module_ConfigModeStatus_Inactive 0x00

/* Private variables----------------------------------------------------------*/

// Private varibales for change between modes management.
uint8_t BetaFit_Mode, Previous_BetaFit_Mode;

// Private varibales for specific mode management.
uint8_t lastMinutesValue, lastStepsValue, ConfigModeStatus, lastPositionValue;

/* Function prototypes -------------------------------------------------------*/

void BetaFit_Setup (void);

void BetaFit_Main (void);

/* BetaFit Main Function prototypes ------------------------------------------*/

void BetaFit_Init_Mode_Main (void);

void BetaFit_Clock_Mode_Main (void);

void BetaFit_Steps_Mode_Main (void);

void BetaFit_Body_Heat_Mode_Main (void);

void BetaFit_Heart_Rate_Mode_Main (void);

void BetaFit_Configuration_Mode_Main (void);

/* Auxiliary Function prototypes ---------------------------------------------*/

void BetaFit_Position_Management (void);

void BetaFit_New_Mode_Begin (void);


/* Functions -----------------------------------------------------------------*/

/**
  * @brief This function configure all the modules's resources.
  * 
  * @retval none.
  */
void BetaFit_Setup (void) {

  lastMinutesValue = 0x00;

  lastStepsValue = 0x00;

  ConfigModeStatus = BetaFit_Main_Module_ConfigModeStatus_Inactive;

  lastPositionValue = BETAFIT_ON_POSITION;

  BetaFit_Init_Mode_Main( );

  // Modules Begin( );
}

/**
  * @brief This function execute the main function of the BetaFit.
  *
  * @retval none.
  */
void BetaFit_Main (void) {

  switch (BetaFit_Mode) {

    case BETAFIT_MODE_INIT:
        BetaFit_Init_Mode_Main ( );
    break;

    case BETAFIT_MODE_CLOCK:
        BetaFit_Clock_Mode_Main ( );
    break;

    case BETAFIT_MODE_STEPS:
        BetaFit_Steps_Mode_Main ( );
    break;

    case BETAFIT_MODE_BH:
        BetaFit_Body_Heat_Mode_Main ( );
    break;

    case BETAFIT_MODE_HR:
        BetaFit_Heart_Rate_Mode_Main ( );
    break;

    case BETAFIT_MODE_CONF:
        BetaFit_Configuration_Mode_Main ( );
    break;

    default:
    break;
  }

}


/* BetaFit Main Function -----------------------------------------------------*/

/**
  * @brief This function execute the Init Mode behavior.
  *
  * @retval none.
  */
void BetaFit_Init_Mode_Main (void) {

  // Display Steps mode logo.
  OLED_Device_Diplay_Menu_Item(BETAFIT_MODE_INIT);

  // Wait 3 seconds.
  delay(3000);

  BetaFit_Mode = BETAFIT_MODE_BH;
}

/**
  * @brief This function execute the Clock Mode behavior.
  *
  * @retval none.
  */
void BetaFit_Clock_Mode_Main (void) {
  
  uint8_t currentMinutesValue = 0, currentHoursValue = 0;

  if (BetaFit_Mode != Previous_BetaFit_Mode) BetaFit_New_Mode_Begin( );

  BetaFit_Position_Management( );

  // User is looking at the device and the display is ON.
  if(Accelerometer_Get_Position() == BETAFIT_ON_POSITION) {

    // Get time data.
    // GetTime();

    // Compare actual minutes value with the pervious one.
    // If these values are different, send new data to the OLED Display.
    if(lastMinutesValue != currentMinutesValue) {
      
      // Update lastMinutesValue.
      lastMinutesValue = currentMinutesValue;

      // Send new data to the OLED Display.
      OLED_Device_Diplay_Clock(currentHoursValue, currentMinutesValue);
    }
  }

  // Repeat each 50 ms (sampling frequency 20 Hz)
  delay(50);
}

/**
  * @brief This function execute the Steps Mode behavior.
  *
  * @retval none.
  */
void BetaFit_Steps_Mode_Main (void) {

  uint8_t currentStepsValue = 0;
  
  if (BetaFit_Mode != Previous_BetaFit_Mode) BetaFit_New_Mode_Begin( );

  BetaFit_Position_Management( );

  // User is looking at the device and the display is ON.
  if(Accelerometer_Get_Position() == BETAFIT_ON_POSITION) {

    // Get step count.
    currentStepsValue = getStepCount();

    // Compare actual value with the pervious one.
    // If these values are different, send new data to the OLED Display.
    if(lastStepsValue != currentStepsValue) {
      
      // Update lastStepsValue.
      lastStepsValue = currentStepsValue;

      // Send new data to the OLED Display.
      OLED_Device_Diplay_Steps (currentStepsValue);
    }
  }

  // Repeat each 50 ms (Sampling frequency 20 Hz)
  delay(50);
}

/**
  * @brief This function execute the Body Heat Mode behavior.
  *
  * @retval none.
  */
void BetaFit_Body_Heat_Mode_Main (void) {

  if (BetaFit_Mode != Previous_BetaFit_Mode) {
    
    BetaFit_New_Mode_Begin( );

    OLED_Device_Display_Measurement_Request(BETAFIT_MODE_BH);
  }
  
    // Show in the display measuring process info.
  OLED_Device_Display_Measurement_Processing(BETAFIT_MODE_BH);

  // Turn temperature sensor on.
  Temperature_Sensor_WakeUp( );

  // Get the measure and represent it in the display.
  OLED_Device_Diplay_BodyHeat( Get_Temperature_Celsius ( ) );

  // Turn temperature sensor off.
  Temperature_Sensor_Sleep ( );

  delay(10000);

  /*
  if (long_keystroke_flag) {
    
    // Deactivate flag.
    long_keystroke_flag = 0x00;

    // Show in the display measuring process info.
    OLED_Device_Display_Measurement_Processing(BETAFIT_MODE_BH);

    // Turn temperature sensor on.
    Temperature_Sensor_WakeUp( );

    // Get the measure and represent it in the display.
    OLED_Device_Diplay_BodyHeat( Get_Temperature_Celsius ( ) );

    // Turn temperature sensor off.
    Temperature_Sensor_Sleep ( );
  }
  */
}

/**
* @brief This function execute the Heart Rate Mode behavior.
*
* @retval none.
*/
void BetaFit_Heart_Rate_Mode_Main (void) {

  if (BetaFit_Mode != Previous_BetaFit_Mode) {
    
    BetaFit_New_Mode_Begin( );

    OLED_Device_Display_Measurement_Request(BETAFIT_MODE_HR);
  }
  /*
  if (long_keystroke_flag) {

    // Deactivate flag.
    long_keystroke_flag = 0x00;

    // Show in the display measuring process info.
    OLED_Device_Display_Measurement_Processing(BETAFIT_MODE_HR);

    // Turn pulse sensor on.
    Pulse_Sensor_WakeUp( );

    // Get the measure and represent it in the display.
    OLED_Device_Diplay_HeartRate( Get_Heart_Rate ( ) );

    // Turn Pulse sensor off.
    Pulse_Sensor_Sleep ( );
  }
  */
}

/**
* @brief This function execute the Configuration Mode behavior.
*
* @retval none.
*/
void BetaFit_Configuration_Mode_Main (void) {

  if (BetaFit_Mode != Previous_BetaFit_Mode) BetaFit_New_Mode_Begin( );
  /*
  if (ConfigModeStatus == BetaFit_ConfigModeStatus_Inactive && long_keystroke_flag = 0xFF) {

    // Deactivate flag.
    long_keystroke_flag = 0x00;

    // Update ConfigModeStatus.
    ConfigModeStatus = BetaFit_ConfigModeStatus_Active;

    // Turn on WiFi interface and web server.
    wifiConnectionBegin( );
  }

  if (ConfigModeStatus == BetaFit_ConfigModeStatus_Active && long_keystroke_flag = 0xFF) {

    // Deactivate flag.
    long_keystroke_flag = 0x00;

    // Update ConfigModeStatus.
    ConfigModeStatus = BetaFit_ConfigModeStatus_Inactive;

    // Turn off WiFi interface and web server.
    wifiConnectionStop( );
  }

  // If ConfigModeStatus is Active, handle web server.
  if (ConfigModeStatus = BetaFit_ConfigModeStatus_Active) webServerLoop( );
  */
}


/* Auxiliary Functions -------------------------------------------------------*/

/**
  * @brief This function execute behavior of the begining of one mode.
  *
  * @retval none.
  */
void BetaFit_New_Mode_Begin (void) {

  // Update Previous_BetaFit_Mode.
  Previous_BetaFit_Mode = BetaFit_Mode;

  // Turn OLED display ON, if it is OFF.
  if (lastPosition == BETAFIT_OFF_POSITION) {
    
    // Update lastPosition.
    lastPosition = BETAFIT_ON_POSITION;

    // Turn OLED display ON.
    OLED_Device_PowerOn( );
  }

  // Display Steps mode logo.
  OLED_Device_Diplay_Menu_Item(BetaFit_Mode);

  // Wait 1.5 seconds.
  delay(1500);
}

/**
  * @brief This function manage the position of the device and the state
  *        of the OLED display (ON or OFF).
  *
  * @retval none.
  */
void BetaFit_Position_Management (void) {

  Accelerometer_Update_Acceleration_Data( );

  // User is looking at the device. If the OLED display is OFF, turn it ON.
  if(Accelerometer_Get_Position( ) == BETAFIT_ON_POSITION && lastPosition == BETAFIT_OFF_POSITION) {
    
    // Update lastPosition.
    lastPosition = BETAFIT_ON_POSITION;
    
    // Turn OLED display ON.
    OLED_Device_PowerOn( );
  }

  // User is NOT looking at the device. If the OLED display is ON, turn it OFF.
  if(Accelerometer_Get_Position( ) == BETAFIT_OFF_POSITION && lastPosition == BETAFIT_ON_POSITION) {

    // Update lastPosition.
    lastPosition = BETAFIT_OFF_POSITION;

    // Turn OLED display OFF.
    OLED_Device_PowerOff( );
  }
}
