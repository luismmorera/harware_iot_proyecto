/**
  ******************************************************************************
  * @file   BetaFit_OLED_Module.c
  * @author Juan Morales Sáez (j.msaez@alumnos.upm.es)
  * @brief  OLED Module.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the OLED module.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "BetaFit_OLED_Module.h" // Module header

#include "BetaFit_OLED_Logos.h"  // Logos file.

/* Private typedef -----------------------------------------------------------*/
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define INFO_SECTION_WIDTH 128 // Info section (blue) width,  in pixels
#define INFO_SECTION_HEIGHT 48 // Info section (blue) height, in pixels

#define CHARACTER_WIDTH  6 // Title section character width,  in pixels
#define CHARACTER_HEIGHT 8 // Title section character height, in pixels

#define OLED_RESET       -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // I2C OLED MOdule Adress


/* Private variables----------------------------------------------------------*/
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* Function prototypes -------------------------------------------------------*/
void OLED_Device_Begin (void);

void OLED_Device_PowerOff (void);
void OLED_Device_PowerOn  (void);

void OLED_Device_Diplay_Menu_Item   (uint8_t muenu_item_id);
void OLED_Device_Diplay_Clock       (uint8_t hour, uint8_t minutes);
void OLED_Device_Diplay_Steps       (int step_number);
void OLED_Device_Diplay_BodyHeat    (float body_heat);
void OLED_Device_Diplay_HeartRate   (uint16_t heart_rate);

void OLED_Device_Display_Measurement_Request (uint8_t Measurement_Type);
void OLED_Device_Display_Measurement_Processing (uint8_t Measurement_Type);

void centerTextInfoSection  (int buffer_length, uint8_t size_factor);

/* Functions -----------------------------------------------------------------*/

/**
* @brief  This function initializes the resources necessary for control and 
*         communication with the OLED module.
*
* @retval None
*/
void OLED_Device_Begin (void) {
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    #ifdef BetaFit_DEBUG
      Serial.println(F("SSD1306 allocation failed"));
    #endif
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();

  // Activate Extended Characters (CP437)
  display.cp437(true);
}

/**
* @brief  This function initializes send the correct command in order to
*         power off the OLED module.
*
* @retval None
*/
void OLED_Device_PowerOff (void) {
  display.ssd1306_command(0xAE);
}

/**
* @brief  This function initializes send the correct command in order to
*         power on the OLED module.
*
* @retval None
*/
void OLED_Device_PowerOn (void) {
  display.ssd1306_command(0xAF);
}

/**
  * @brief  This function sends to the OLED display the title and logo 
  *         corresponding to the working mode in which the program is 
  *         currently running.
  *
  * @param  (uint8_t) muenu_item_id:  Identifies the mode of work which
  *         icon is to be represented in the OLED display.
  *
  * @retval None
  */
void OLED_Device_Diplay_Menu_Item (uint8_t muenu_item_id) {

  switch (muenu_item_id) {

    case BETAFIT_MODE_INIT:
      // Clear the buffer
      display.clearDisplay();

      // Draw Title screen section.
      display.setTextSize(2); // Draw 2X-scale text
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(19, 0);
      display.println(F("BetaFit"));

      // Draw Info screen section.
      display.drawBitmap(0, 16, BETAFIT_LOGO, LOGO_WIDTH, LOGO_HEIGHT, 1);
      
      // Show the display buffer on the screen.
      display.display();
    break;

    case BETAFIT_MODE_CLOCK:
      // Clear the buffer
      display.clearDisplay();

      // Draw Title screen section.
      display.setTextSize(2); // Draw 2X-scale text
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(34, 0);
      display.println(F("Clock"));

      // Draw Info screen section.
      display.drawBitmap(0, 16, CLOCK_LOGO, LOGO_WIDTH, LOGO_HEIGHT, 1);
      
      // Show the display buffer on the screen.
      display.display();
    break;

    case BETAFIT_MODE_STEPS:
      // Clear the buffer
      display.clearDisplay();

      // Draw Title screen section.
      display.setTextSize(2); // Draw 2X-scale text
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(34, 0);
      display.println(F("Steps"));

      // Draw Info screen section.
      display.drawBitmap(0, 16, STEPS_LOGO, LOGO_WIDTH, LOGO_HEIGHT, 1);
      
      // Show the display buffer on the screen.
      display.display();
    break;

    case BETAFIT_MODE_BH:
      // Clear the buffer
      display.clearDisplay();

      // Draw Title screen section.
      display.setTextSize(2); // Draw 2X-scale text
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(10, 0);
      display.println(F("Body Heat"));

      // Draw Info screen section.
      display.drawBitmap(0, 16, THERMOMETER_LOGO, LOGO_WIDTH, LOGO_HEIGHT, 1);
      
      // Show the display buffer on the screen.
      display.display();
    break;

    case BETAFIT_MODE_HR:
      // Clear the buffer
      display.clearDisplay();

      // Draw Title screen section.
      display.setTextSize(2); // Draw 2X-scale text
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(7, 0);
      display.println(F("Heart Rate"));

      // Draw Info screen section.
      display.drawBitmap(0, 16, HR_LOGO, LOGO_WIDTH, LOGO_HEIGHT, 1);
      
      // Show the display buffer on the screen.
      display.display();
    break;

    case BETAFIT_MODE_CONF:
      // Clear the buffer
      display.clearDisplay();

      // Draw Title screen section.
      display.setTextSize(2); // Draw 2X-scale text
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(29, 0);
      display.println(F("Config"));

      // Draw Info screen section.
      display.drawBitmap(0, 16, GEAR_LOGO, LOGO_WIDTH, LOGO_HEIGHT, 1);
      
      // Show the display buffer on the screen.
      display.display();
    break;

    default:
      // Clear the buffer
      display.clearDisplay();
    break;
  }
}

/**
  * @brief  This function sends to the OLED display the title and the data
  *         corresponding to the 'Clock' working mode.
  *
  * @param  (uint8_t) hour: Value to be represented in the OLED display.
  * @param  (uint8_t) minutes: Value to be represented in the OLED display.
  *
  * @retval None
  */
void OLED_Device_Diplay_Clock (uint8_t hour, uint8_t minutes) {

  char buffer[5];
 
  sprintf(buffer, "%02u:%02u", hour, minutes);

  // Clear the display buffer
  display.clearDisplay();

  // Draw Title screen section.
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(34, 0);
  display.println(F("Clock"));

  // Draw Info screen section.
  display.setTextSize(3); // Draw 3X-scale text
  display.setTextColor(SSD1306_WHITE);
  centerTextInfoSection(sizeof(buffer), 3);
  display.print(buffer);

  // Show the display buffer on the screen.
  display.display();
}

/**
  * @brief  This function sends to the OLED display the title and the data
  *         corresponding to the 'Steps' working mode.
  *
  * @param  (int) step_number: Value to be represented in the OLED display.
  *
  * @retval None
  */
void OLED_Device_Diplay_Steps (int step_number) {
  
  uint8_t buffer_length;

  if (step_number < 10) buffer_length = 1;
  else if (step_number < 100) buffer_length = 2;
  else if (step_number < 1000) buffer_length = 3;
  else if (step_number < 10000) buffer_length = 4;
  else buffer_length = 5;
  
  char buffer[buffer_length];
 
  sprintf(buffer, "%u", step_number);

  // Clear the display buffer
  display.clearDisplay();

  // Draw Title screen section.
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(34, 0);
  display.println(F("Steps"));

  // Draw Info screen section.
  display.setTextSize(3); // Draw 3X-scale text
  display.setTextColor(SSD1306_WHITE);
  centerTextInfoSection(sizeof(buffer), 3);
  display.print(buffer);

  // Show the display buffer on the screen.
  display.display();
}

/**
  * @brief  This function sends to the OLED display the title and the data
  *         corresponding to the 'Body Heat' working mode.
  *
  * @param  (float) step_number: Value to be represented in the OLED display.
  *
  * @retval None
  */
void OLED_Device_Diplay_BodyHeat (float body_heat) {
    
  char buffer[5];

  sprintf(buffer, "%04.1fxC", body_heat);

  for (int i = 0; i < sizeof(buffer); i++){
    if(buffer[i] == 'x') buffer[i] = 0xF8;
  }

  // Clear the display buffer
  display.clearDisplay();

  // Draw Title screen section.
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(F("Body Heat"));

  // Draw Info screen section.
  display.setTextSize(3); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  centerTextInfoSection(sizeof(buffer), 3);
  display.print(buffer);
  
  // Show the display buffer on the screen.
  display.display();
}

/**
  * @brief  This function sends to the OLED display the title and the data
  *         corresponding to the 'Heart Rate' working mode.
  *
  * @param  (uint16_t) heart_rate: Value to be represented in the OLED display.
  *
  * @retval None
  */
void OLED_Device_Diplay_HeartRate (uint16_t heart_rate) {
  
  uint8_t buffer_length;

  if (heart_rate < 10) buffer_length = 1;
  else if (heart_rate < 100) buffer_length = 2;
  else buffer_length = 3;
  
  char buffer[buffer_length];
 
  sprintf(buffer, "%u", heart_rate);

  // Clear the display buffer
  display.clearDisplay();

  // Draw Title screen section.
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(7, 0);
  display.println(F("Heart Rate"));

  // Draw Info screen section.
  display.setTextSize(3); // Draw 3X-scale text
  display.setTextColor(SSD1306_WHITE);
  centerTextInfoSection(sizeof(buffer), 3);
  display.print(buffer);

  // Show the display buffer on the screen.
  display.display();
}

void OLED_Device_Display_Measurement_Request (uint8_t Measurement_Type) {

  // Clear the display buffer
  display.clearDisplay();

  // Draw Title screen section.
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);

  if (Measurement_Type == BETAFIT_MODE_BH){
    display.setCursor(10, 0);
    display.println(F("Body Heat"));
  }
  
  if (Measurement_Type == BETAFIT_MODE_HR) {
    display.setCursor(7, 0);
    display.println(F("Heart Rate"));
  }

  // Draw Info screen section.
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(13, 16);
  display.println(F("Press to"));

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(34, 32);
  display.println(F("start"));

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 48);
  display.println(F("Measuring"));

  // Show the display buffer on the screen.
  display.display();
}

void OLED_Device_Display_Measurement_Processing (uint8_t Measurement_Type) {

  // Clear the display buffer
  display.clearDisplay();

  // Draw Title screen section.
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(F("Measuring"));
  
  // Draw Info screen section.

  if (Measurement_Type == BETAFIT_MODE_BH) display.drawBitmap(0, 16, THERMOMETER_LOGO_LOGO, LOGO_WIDTH, LOGO_HEIGHT, 1);

  if (Measurement_Type == BETAFIT_MODE_HR) display.drawBitmap(0, 16, HR_LOGO, LOGO_WIDTH, LOGO_HEIGHT, 1);

  // Show the display buffer on the screen.
  display.display();
}

/**
  * @brief  This function centers text in the information section of the display.
  *
  * @param  (int) buffer_length: Length of the information to be represented in 
  *         the OLED display.
  * @param  (uint8_t) size_factor: Enlargement factor used.
  *
  * @retval None
  */
void centerTextInfoSection (int buffer_length, uint8_t size_factor) {
  
  uint8_t height = 0, width = 0;

  height = 16 + ((INFO_SECTION_HEIGHT - size_factor*CHARACTER_HEIGHT) / 2);
  width  = (INFO_SECTION_WIDTH  - size_factor*CHARACTER_WIDTH*buffer_length)  / 2;
  
  display.setCursor(width, height);
}