#include <Wire.h>

const uint8_t MLX90614_I2CADDR = 0x5A;
const uint8_t MLX90614_TOBJ1 = 0x07;

/*


void configuracion_inicial(uint16_t slave_addr, uint8_t registro, uint8_t valor);
uint16_t leer_registro(uint8_t slave_addr, uint8_t registro, uint8_t num_bytes);

uint16_t temp_bin;
float temperatura;
  uint8_t buffer[2];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  temperatura = 0;
  temp_bin = 0;
  buffer[0] = 0;
  buffer[1] = 0;
  configuracion_inicial(MLX90614_I2CADDR,aa,aa);
}

void loop() {
  // put your main code here, to run repeatedly:
  temp_bin = leer_registro(MLX90614_I2CADDR,MLX90614_I2CADDR,2);
  Serial.println(temp_bin);
  delay(1000);
}

/*
 * Librería personalziada I2C
 */
/*
 void configuracion_inicial(uint8_t slave_addr, uint8_t registro, uint8_t valor){
  //Wire.begin();
  Wire.beginTransmission(slave_addr);
  if(Wire.available()){
    Wire.write(registro);
    Wire.write(valor);
    Wire.endTransmission();
  }else{
    Serial.println("Wire not available");
  }
 }

uint16_t leer_registro(uint8_t slave_addr, uint8_t registro, uint8_t num_bytes){

  uint16_t resultado;
  uint8_t i = 0;
  Wire.beginTransmission(slave_addr);
  Wire.write(registro);
  Wire.requestFrom(slave_addr, num_bytes);  // request 6 bytes from slave device #8
    while(Wire.available()){
      buffer[i] = Wire.read();
      i++;
    }
    Wire.endTransmission();
  resultado = buffer[0] | (buffer[1] << 8);
 }
 */
 int registro_temperatura;
 bool error_temperatura;
 byte trama[] = { 0x00,0x00};

 void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  error_temperatura = true;
  Wire.beginTransmission(MLX90614_I2CADDR);
  Wire.write(MLX90614_TOBJ1);
  Wire.endTransmission(false);
  Wire.requestFrom(MLX90614_I2CADDR,2);
  if(Wire.available()==2){
    trama[0] = Wire.read();
    trama[1] = Wire.read();

    registro_temperatura = trama[0] | (trama[1] << 8);
    Serial.println((float)registro_temperatura*0.02 -273.15);
  }
  delay(1000);
}
