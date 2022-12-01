#include <Wire.h>

#define SDA_PIN 1
#define SCL_PIN 2

#define PULSE_SENSOR_ADDR 0x57

#define FIFO_DATA          0x07

//Configuration registers
#define FIFO_CONFIGURATION 0x08
#define MODE_CONFIGURATION 0x09
#define SP02_CONFIGURATION 0x0A
#define LED_PULSE_CONFIGURATION 0x0C

void pulse_sensor_init();
void leer_pulse_sensor();

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Inicialización de los recursos I2C");
  analogReference(DEFAULT);
  pulse_sensor_init();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("");
  Serial.println("LECTURA");
  leer_pulse_sensor();
  delay(1000);
}

void pulse_sensor_init(){
  //Podemos jugar con el autoincremento.
  //Wire.begin();
  Serial.println("Se inicia la configuración de datos");
  if(Wire.available()){
    Wire.beginTransmission(PULSE_SENSOR_ADDR);
    Wire.write(FIFO_CONFIGURATION);
    Wire.write(0x4F);
    Wire.endTransmission();

    Wire.beginTransmission(PULSE_SENSOR_ADDR);
    Wire.write(MODE_CONFIGURATION);
    Wire.write(0x02);
    Wire.endTransmission();

    Wire.beginTransmission(PULSE_SENSOR_ADDR);
    Wire.write(SP02_CONFIGURATION);
    Wire.write(0x2F);
    Wire.endTransmission();

    Wire.beginTransmission(PULSE_SENSOR_ADDR);
    Wire.write(LED_PULSE_CONFIGURATION);
    Wire.write(0x1F);
    Wire.endTransmission();
  }else{
    Serial.println("No se ha podido establecer conexión con el dispositivo esclavo");
  }
  //En caso de utilizar autoincremento:
  /*
  Wire.beginTransmission(PULSE_SENSOR_ADDR);
  Wire.write(FIFO_CONFIGURATION);
  Wire.write(0x4F);
  Wire.write(0x02);
  Wire.write(0x2F);
  Wire.write(0x1F);
  Wire.endTransmission();
  
   */
}

void leer_pulse_sensor(){
  /*
   * En la operación de lectura lo que tenemos que hacer es una operación de escritura sobre un registro, de forma que el puntero se mueva
   * a ese registro, después se hace una operación de lectura a donde esté apuntando ese puntero, es decir, el registro sobre el cual hemos 
   * escrito con anterioridad.
   */
  //Wire.begin(SDA_PIN, SCL_PIN);
  //Wire.begin();
  Wire.write(FIFO_DATA);
  Wire.requestFrom(PULSE_SENSOR_ADDR, 1);  // request 6 bytes from slave device #8
  if (Wire.available()) {  // slave may send less than requested
    Serial.println("Dispositivo disponible");
    byte b = Wire.read();     // receive a byte as character
    Serial.print(b);          // print the character
  }
  Wire.endTransmission();
}

/*
 * Librería personalziada I2C
 */
/*
 void configuracion_inicial(uint16_t slave_addr, uint8_t registro, uint8_t valor){
  //Wire.begin();
  Wire.beginTransimission(slave_addr);
  Wire.write(registro);
  Wire.write(valor);
  Wire.endTransmission();
 }

void leer_registro(uint16_t slave_addr, uint8_t registro, uint8_t num_bytes){
  //Wire.begin();
  Wire.beginTransimission(slave_addr);
  Wire.write(registro);
  Wire.requestFrom(slave_addr, num_bytes);  // request 6 bytes from slave device #8
  Wire.endTransmission();
 }
*/
