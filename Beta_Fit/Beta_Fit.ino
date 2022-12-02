  #include <Arduino.h>
  #include <Wire.h>
  #include <PolledTimeout.h>

// #include "I2C_Module.h"

#define SLAVE_ADDR 0x3A

void I2C_Device_Begin (void);
void I2C_Device_End   (void);

bool I2C_Device_Detected (uint8_t slave_address);

void I2C_Device_Send_Data (uint8_t slave_address, uint8_t *slave_register, uint8_t *buffer);
void I2C_Device_Read_Data (uint8_t slave_address, uint8_t *slave_register, uint8_t *buffer, uint8_t buffer_size);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Inicialización de los recursos I2C");

  I2C_Device_Begin();
  I2C_Device_Detected(0x3A);
  I2C_Device_End();
}

void loop() {
}

#define SDA_PIN 4
#define SCL_PIN 5

const int16_t I2C_SLAVE = 0x08;

/* Private variables----------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
void I2C_Device_Begin (void) {
  Wire.begin(SDA_PIN, SCL_PIN);
}

void I2C_Device_End (void) {
  Wire.end();
}

bool I2C_Device_Detected (uint8_t slave_address) {

  // A basic scanner, see if it ACK's.
  Wire.beginTransmission(slave_address);
  
  if (Wire.endTransmission() == 0) return true;
  else return false;
}

void I2C_Device_Send_Data (uint8_t slave_address, uint8_t slave_register, uint8_t buffer) {
  // Strat the transmission. Select Slave.
  Wire.beginTransmission(slave_address);
  
  // Select target register in the slave.
  Wire.write(slave_register);
  
  // Send data to slave.
  Wire.write(buffer);
  
  // Finish the transmission.
  Wire.endTransmission(true);
}

void I2C_Device_Read_Data (uint8_t slave_address, uint8_t slave_register, uint8_t *buffer, uint8_t buffer_size) {
  
  uint8_t buffer_index = 0;

  // Strat the transmission. Select Slave.
  Wire.beginTransmission(slave_address);
  
  // Select target register in the slave.
  Wire.write(slave_register);
  
  // Request buffer_size bytes to the slave device with the desired slave_address.
  Wire.requestFrom(slave_address, buffer_size);  

  // Slave may send less than requested.
  while(Wire.available())
    
    // Receive a byte from the slave.
    buffer[buffer_index] = Wire.read();
    
    // Increment buffer index.
    ++buffer_index;
  }

  // Finish the transmission.
  Wire.endTransmission(true);
}