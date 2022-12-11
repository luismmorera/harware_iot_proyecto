/**
  ******************************************************************************
  * @file   I2C_Module.c
  * @author Juan Morales Sáez (j.msaez@alumnos.upm.es)
  * @brief  I2C Module.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module manages the I2C bus.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "BetaFit_I2C_Module.h"             // Module header

/* Private typedef -----------------------------------------------------------*/
#define SDA_PIN 4
#define SCL_PIN 5

//const int16_t I2C_SLAVE = 0x08;

/* Private variables----------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
void I2C_Device_Begin (void) {
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.begin(115200);
}

/*
void I2C_Device_End (void) {
  Wire.end();
}
*/

bool I2C_Device_Detected (uint8_t slave_address) {

  // A basic scanner, see if it ACK's.
  Wire.beginTransmission(slave_address);
  
  if (Wire.endTransmission() == 0) return true;
  else return false;
}

void I2C_Device_Send_Data (uint8_t slave_address, uint8_t slave_register, uint8_t *buffer, uint8_t buffer_size) {
  // Strat the transmission. Select Slave.
  uint8_t buffer_index = 0;
  Wire.beginTransmission(slave_address);
  
  // Select target register in the slave.
  Wire.write(slave_register);
  
  // Send data to slave.
  //Wire.write(buffer);

  Wire.write(buffer, buffer_size);
  /*
  while(buffer_index<buffer_size){
    Wire.write(buffer, buffer_size);
  }
  */
  // Finish the transmission.
  Wire.endTransmission();
}

void I2C_Device_Read_Data (uint8_t slave_address, uint8_t slave_register, uint8_t *buffer, uint8_t buffer_size) {
  
  uint8_t buffer_index = 0;

  // Strat the transmission. Select Slave.
  Wire.beginTransmission(slave_address);
  
  // Select target register in the slave.
  Wire.write(slave_register);
  
  Wire.endTransmission(false); //Esto es clave por algún motivo.
  
  // Request buffer_size bytes to the slave device with the desired slave_address.
  Wire.requestFrom(slave_address, buffer_size);  

  // Slave may send less than requested.
  if(Wire.available()==buffer_size) {
    while(buffer_index < buffer_size){
      
      // Receive a byte from the slave.
      buffer[buffer_index] = Wire.read();
      
      // Increment buffer index.
      ++buffer_index;
    }
  }

  // Finish the transmission.
  Wire.endTransmission(true);
}
