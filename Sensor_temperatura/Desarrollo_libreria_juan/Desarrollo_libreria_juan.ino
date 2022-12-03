/**
  ******************************************************************************
  * @file   Sensor_temperatura.c
  * @author Mario López Parejo (mario.lopezp@alumnos.upm.es)
  * @brief  I2C Module.
  *
  * @note   HwIoT - Final Design - BetaFit Project.
  *         This module access and processes the information given by the
  *         temperature sensor MLX90614.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "BetaFit_I2C_Module.h"             // Module header

/* Private typedef -----------------------------------------------------------*/

const uint8_t MLX90614_I2C_ADDR = 0x5A;
const uint8_t MLX90614_TOBJ1 = 0x07;

int registro_temperatura;

//#define MLX90614_I2C_ADDR 0x5A
//#define MLX90614_TOBJ1 0x07

uint8_t buffer[2] = {0,0};

void setup() {
  // put your setup code here, to run once:
  I2C_Device_Begin();
  Serial.begin(115200);
  
  registro_temperatura = 0;
  
  while(!I2C_Device_Detected(MLX90614_I2C_ADDR)){
    Serial.print(".");
    delay(100);
  }
  Serial.println("");
  Serial.println("Device detected");

  Serial.println("Tamaño del array:  ");
  Serial.print(sizeof(buffer));
  //Configuración inicial de los registros: En este sensor no es necesario
  I2C_Device_Send_Data(MLX90614_I2C_ADDR,MLX90614_TOBJ1,buffer[0]);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  I2C_Device_Read_Data(MLX90614_I2C_ADDR, MLX90614_TOBJ1, buffer, sizeof(buffer));
  Serial.println("");
  Serial.print("Buffer[0] =");
  Serial.println(buffer[0]);
  Serial.print("Buffer[1] =");
  Serial.println(buffer[1]);

  registro_temperatura = buffer[0] | (buffer[1] << 8);
  Serial.println((float)registro_temperatura*0.02 -273.15);

  delay(1000);

}
