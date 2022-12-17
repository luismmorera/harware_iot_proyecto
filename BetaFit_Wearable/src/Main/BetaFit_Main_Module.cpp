/**
  ******************************************************************************
  * @file   BetaFit_Main_Module.cpp
  * @author Juan Morales Sáez (j.msaez@alumnos.upm.es)
  * @brief  Main Module.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module is the main module of the BetaFit Project.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "BetaFit_Main_Module.h" // Module header

// BetaFit Libraries
#include "../BetaFit_Definitions.h"

#include "../accelerometer/BetaFit_Accelerometer_Module.h"
#include "../accelerometer/BetaFit_SetpDetector_Module.h"
#include "../temperatureSensor/BetaFit_Temperature_Sensor_Module.h"
#include "../OLED/BetaFit_OLED_Module.h"
#include "../RTC/RTC.h"
#include "../buttonHandler/buttonHandler.h"
#include "../pulseSensor/pulseSensor.h"

#include "../wifiConnection/wifiConnection.h"
#include "../webServer/webServer.h"

#include "../flash/flash.h"
#include "../jsonManager/jsonManager.h"

/* Private typedef -----------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

#ifndef STASSID
#define STASSID "MOVISTAR_D157"
#define STAPSK "mgD9KG23ju3jhPz7Y5F6"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

// Private varibales for change between modes management.
uint8_t BetaFit_Mode, Previous_BetaFit_Mode;

// Private varibales for specific mode management.
uint8_t lastMinutesValue, lastStepsValue, lastPositionValue;

bool ConfigModeStatus;

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

String Get_Actual_TimeStamp (void);


/* Functions -----------------------------------------------------------------*/

/**
  * @brief This function configure all the modules's resources.
  * 
  * @retval none.
  */
void BetaFit_Setup (void) {

  lastMinutesValue = 0x00;
  lastStepsValue = 0x00;

  ConfigModeStatus = false;

  lastPositionValue = BETAFIT_OFF_POSITION;

  Accelerometer_Device_Begin( );

  buttonStart();

  flashBegin( );

  OLED_Device_Begin( );

  init_hr_sensor( );

  RTC_Device_Begin(ssid, password);

  Temperature_Sensor_Begin( );

  webServerBegin( );

  // Represent Logo.
  BetaFit_Init_Mode_Main();
}

/**
  * @brief This function execute the main function of the BetaFit.
  *
  * @retval none.
  */
void BetaFit_Main (void) {

  buttonStateMachine( );

  switch (BetaFit_Mode) {

    case BETAFIT_MODE_CLOCK:
      BetaFit_Clock_Mode_Main ( );
      
      if (BUTTON_SHORT_PULSE_FLAG) {
        // Deactivate flag.
        BUTTON_SHORT_PULSE_FLAG = false;

        BetaFit_Mode = BETAFIT_MODE_STEPS;  
      }

      // Don't care about long pulsations. Deactivate flag.
      if (BUTTON_LONG_PULSE_FLAG) BUTTON_LONG_PULSE_FLAG = false;
    break;

    case BETAFIT_MODE_STEPS:
      BetaFit_Steps_Mode_Main ( );
      
      if (BUTTON_SHORT_PULSE_FLAG) {
        // Deactivate flag.
        BUTTON_SHORT_PULSE_FLAG = false;

        BetaFit_Mode = BETAFIT_MODE_BH;
      }

      // Don't care about long pulsations. Deactivate flag.
      if (BUTTON_LONG_PULSE_FLAG) BUTTON_LONG_PULSE_FLAG = false;
    break;

    case BETAFIT_MODE_BH:
      BetaFit_Body_Heat_Mode_Main ( );

      if (BUTTON_SHORT_PULSE_FLAG) {
        // Deactivate flag.
        BUTTON_SHORT_PULSE_FLAG = false;

        BetaFit_Mode = BETAFIT_MODE_HR;
      }

      // Don't care about long pulsations. Deactivate flag.
      if (BUTTON_LONG_PULSE_FLAG) BUTTON_LONG_PULSE_FLAG = false;
    break;

    case BETAFIT_MODE_HR:
      BetaFit_Heart_Rate_Mode_Main ( );
      
      if (BUTTON_SHORT_PULSE_FLAG) {
        // Deactivate flag.
        BUTTON_SHORT_PULSE_FLAG = false;

        BetaFit_Mode = BETAFIT_MODE_CONF;
      }

    break;

    case BETAFIT_MODE_CONF:
        BetaFit_Configuration_Mode_Main ( );

        if (BUTTON_SHORT_PULSE_FLAG) {
          // Deactivate flag.
          BUTTON_SHORT_PULSE_FLAG = false;

          // Go to net mode onle if ConfigModeStatus is deactuivated.
          if (!ConfigModeStatus) BetaFit_Mode = BETAFIT_MODE_USER_INFO;
        }
    break;

    case BETAFIT_MODE_CONF:
      BetaFit_User_Info_Mode_Main ( );

      if (BUTTON_SHORT_PULSE_FLAG) {
        // Deactivate flag.
        BUTTON_SHORT_PULSE_FLAG = false;

        BetaFit_Mode = BETAFIT_MODE_CLOCK;
      }

      // Don't care about long pulsations. Deactivate flag.
      if (BUTTON_LONG_PULSE_FLAG) BUTTON_LONG_PULSE_FLAG = false;
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

  Previous_BetaFit_Mode = BETAFIT_MODE_INIT;
  BetaFit_Mode = BETAFIT_MODE_CLOCK;
}

/**
  * @brief This function execute the Clock Mode behavior.
  *
  * @retval none.
  */
void BetaFit_Clock_Mode_Main (void) {
  
  uint8_t currentMinutesValue = 0, currentHoursValue = 0;

  if (BetaFit_Mode != Previous_BetaFit_Mode){
    BetaFit_New_Mode_Begin( );
    
    // Send new data to the OLED Display.
    OLED_Device_Diplay_Clock(get_Hours(), get_Minutes());
  } 

  BetaFit_Position_Management( );

  // User is looking at the device and the display is ON.
  if(Accelerometer_Get_Position() == BETAFIT_ON_POSITION) {

    // Get time data.
    currentMinutesValue = get_Minutes( );
    currentHoursValue = get_Hours( );

    if (currentMinutesValue == 0 && currentHoursValue == 24) {
      setStepsEntry(get_Month( ), get_Day( ), (uint32_t) getStepCount( ));
      
      resetStepCount( );
    }

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
  
  if (BetaFit_Mode != Previous_BetaFit_Mode){
    BetaFit_New_Mode_Begin( );
    
    // Send new data to the OLED Display.
    OLED_Device_Diplay_Steps (getStepCount());
  } 

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

  float temperature;
  
  Accelerometer_Update_Acceleration_Data( );

  if (BetaFit_Mode != Previous_BetaFit_Mode){
    BetaFit_New_Mode_Begin( );
    OLED_Device_Display_Measurement_Request(BETAFIT_MODE_BH);
  } 

  // User is looking at the device. If the OLED display is OFF, turn it ON.
  if (Accelerometer_Get_Position( ) == BETAFIT_MEAS_BH_POSITION) {

    // Show in the display measuring process info.
    OLED_Device_Display_Measurement_Processing(BETAFIT_MODE_BH);

    // Wait 500 ms to ensure that user is in the correct postion.
    delay(500);

    // Turn temperature sensor on.
    Temperature_Sensor_WakeUp( );

    temperature = Get_Temperature_Celsius( );

    // Get the measure and represent it in the display.
    OLED_Device_Diplay_BodyHeat(temperature);

    setTemperatureEntry(Get_Actual_TimeStamp( ), temperature, compareTemperature(temperature));

    // Turn temperature sensor off.
    Temperature_Sensor_Sleep ( );

    // Wait 5 s showing the last measurement.
    delay(5000);
  }
}

/**
* @brief This function execute the Heart Rate Mode behavior.
*
* @retval none.
*/
void BetaFit_Heart_Rate_Mode_Main (void) {

  uint16_t heart_rate = 0;

  if (BetaFit_Mode != Previous_BetaFit_Mode) {
    
    BetaFit_New_Mode_Begin( );

    OLED_Device_Display_Measurement_Request(BETAFIT_MODE_HR);
  }

  if (BUTTON_LONG_PULSE_FLAG) {
    // Deactivate flag.
    BUTTON_LONG_PULSE_FLAG = false;

    // Show in the display measuring process info.
    OLED_Device_Display_Measurement_Processing(BETAFIT_MODE_HR);

    heart_rate = (uint16_t) realizar_medidas( );

    // Get the measure and represent it in the display.
    OLED_Device_Diplay_HeartRate(heart_rate);

    if (heart_rate != 1) setHeartRateEntry(Get_Actual_TimeStamp( ), (float) heart_rate, compareHeartRate(heart_rate));

    // Wait 5 s showing the last measurement.
    delay(5000);

    // Request for a new measuring.
    OLED_Device_Display_Measurement_Request(BETAFIT_MODE_HR);
  }
}

/**
  * @brief This function execute the Configuration Mode behavior.
  *
  * @retval none.
  */
void BetaFit_Configuration_Mode_Main (void) {

  if (BetaFit_Mode != Previous_BetaFit_Mode) BetaFit_New_Mode_Begin( );

  if (BUTTON_LONG_PULSE_FLAG) {
    // Deactivate flag.
    BUTTON_LONG_PULSE_FLAG = false;
    
    if (ConfigModeStatus) {
      // Update ConfigModeStatus.
      ConfigModeStatus = false;

      // Turn off WiFi interface and web server.
      wifiConnectionStop( );

      // Display WiFi Off icon.
      OLED_Device_Display_Wifi_Off( );
    }

    else {
      // Update ConfigModeStatus.
      ConfigModeStatus = true;

      // Display WiFi On icon while connecting.
      OLED_Device_Display_Wifi_Connecting( );

      // Turn on WiFi interface and web server.
      wifiConnectionStart(STASSID, STAPSK);

      // Display WiFi On icon and the IP assigned.
      OLED_Device_Display_Wifi_On(getIP( ));
    }
  }

  // If ConfigModeStatus is true, handle web server.
  if (ConfigModeStatus) webServerLoop( );
}

/**
  * @brief This function execute the User Info Mode behavior.
  *
  * @retval none.
  */
void BetaFit_User_Info_Mode_Main (void) {

  if (BetaFit_Mode != Previous_BetaFit_Mode) {
    BetaFit_New_Mode_Begin( );

    OLED_Device_Display_User_Info((String) getUserName( ), (float) getUserIMC( ));
  }

  BetaFit_Position_Management( );
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
  if (lastPositionValue == BETAFIT_OFF_POSITION) {
    
    // Update lastPositionValue.
    lastPositionValue = BETAFIT_ON_POSITION;

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
  if(Accelerometer_Get_Position( ) == BETAFIT_ON_POSITION && lastPositionValue == BETAFIT_OFF_POSITION) {
    
    // Update lastPositionValue.
    lastPositionValue = BETAFIT_ON_POSITION;
    
    // Turn OLED display ON.
    OLED_Device_PowerOn( );
  }

  // User is NOT looking at the device. If the OLED display is ON, turn it OFF.
  if(Accelerometer_Get_Position( ) == BETAFIT_OFF_POSITION && lastPositionValue == BETAFIT_ON_POSITION) {

    // Update lastPositionValue.
    lastPositionValue = BETAFIT_OFF_POSITION;

    // Turn OLED display OFF.
    OLED_Device_PowerOff( );
  }
}

/**
  * @brief This function get the actual time and format it to a determinated
  *        time stamp format.
  *
  * @retval none.
  */
String Get_Actual_TimeStamp (void) {
  char timeStamp[20];
  
  // Time Stamp. Should be "YYYY-MM-DDTHH:MM:SS" format.
  sprintf(timeStamp, "%04u-%02u-%02uT%02u:%02u:%02", get_Year( ), get_Month( ), get_Day( ), get_Hours( ), get_Minutes( ), get_Seconds( ));

  return String(timeStamp);
}
