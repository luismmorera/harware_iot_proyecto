#include <Adafruit_I2CDevice.h>
#include <AsyncTimer.h>

//Dirección I2C del sensor de pulso.
//#define PULSE_SENSOR_ADDR 0xAE
//#define PULSE_SENSOR_ADDR 0xAF
#define PULSE_SENSOR_ADDR 0x57

//Declaración de funciones del programa
void configuracion_pulse_sensor_inicial(Adafruit_I2CDevice i2c_dev);
void realizar_medidas();

//Declaración de variables globales
 Adafruit_I2CDevice i2c_pulse_sensor = Adafruit_I2CDevice(PULSE_SENSOR_ADDR);
 AsyncTimer timer;
uint8_t buffer_leidos[16];

#define I2C_SPEED_FAST 

//Se definen los registros a los que se va a acceder:

#define FIFO_DATA          0x07

//Configuration registers
#define FIFO_CONFIGURATION 0x08
#define MODE_CONFIGURATION 0x09
#define SP02_CONFIGURATION 0x0A

void setup() {
  // put your setup code here, to run once:
  analogReference(DEFAULT);
  Serial.begin(115200);

  Serial.println(PULSE_SENSOR_ADDR, HEX);

  Serial.println("I2C device read and write test");

  //Si este while no funciona es normal, los sensores no suelen responder.
  int contador = 0;
  while(!i2c_pulse_sensor.begin(true) && contador < 10){
    Serial.print(".");
    contador++;
    delay(500);
  }
  
  if(i2c_pulse_sensor.detected()){
    Serial.println("Se ha detectado");
  }else{
    Serial.println("No se ha detectado");
  }
  
  Serial.println("Device found at address 0x");
  Serial.print(i2c_pulse_sensor.address(), HEX);
  Serial.println("");
  configuracion_pulse_sensor_inicial(i2c_pulse_sensor);
}

void loop() {
  realizar_medidas();
  delay(1000);
}

void configuracion_pulse_sensor_inicial( Adafruit_I2CDevice i2c_dev ){
  //Para la escritura en los registros había que hacer lo siguiente:
  //Escribir dirección del registro. Escribir dato del registro.
  /*
   * byte ledBrightness = 60; //Options: 0=Off to 255=50mA -> CHECK
byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green -> CHECK
byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200 
int pulseWidth = 411; //Options: 69, 118, 215, 411 -> CHECK
int adcRange = 4096; //Options: 2048, 4096, 8192, 16384-> CHECK
   */
  uint8_t buffer[5];
  //buffer[0] = FIFO_CONFIGURATION
  buffer[0] = MODE_CONFIGURATION;
  buffer[1] = 0x02;
  buffer[2] = 0x01;//Como contamos con el autoincremento, se configura el siguiente registro, es decir el 0xA
  buffer[3] = 0x00;//0x0B
  buffer[4] = 0x1F;//0x0C
  if(i2c_dev.write(buffer,5,true)){
    Serial.println("Se ha realizado la configuracion inicial ");
  }else{
    Serial.println("No se ha realizado la configuracion inicial ");
  }
}

void realizar_medidas(){
  ////Read register FIDO_DATA in (3-byte * number of active LED) chunks
  uint8_t reg_lectura[1] = {0x07};
  // Try to read 32 bytes
  //i2c_pulse_sensor.write_then_read(buffer_leidos, 32);
  //La FIFO almacena 32 valores, de los cuales solo nos interesan el primer byte de cada grupo de 3 que se almacenan.
  if(i2c_pulse_sensor.write_then_read(reg_lectura, 1, buffer_leidos, 16, false)){
    Serial.println("SE HA LEIDO");
  }else{
    Serial.println("NO SE HA LEIDO");
  }
  Serial.print("Read: ");
  for (uint8_t i=0; i<16; i++) {
    Serial.print("0x"); Serial.print(buffer_leidos[i], HEX); Serial.print(", ");
  }
  Serial.println();

}
