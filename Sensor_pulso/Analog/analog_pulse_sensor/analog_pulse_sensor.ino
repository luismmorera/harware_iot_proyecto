#include <AsyncTimer.h>
#include "hardware.h"

int contador_pulsos;
int tension_entrada;
bool init_medida;
bool fin_medida;
bool primera_deteccion;

AsyncTimer timer_muestreo;
AsyncTimer timer_init_medida;
AsyncTimer timer_duracion_medida;

const int umbral_deteccion = 500;

void init_hr_sensor();
void switch_off_hr_sensor();
void realizar_medidas();
void deshabilitarMedida();
void iniciar_Medida();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  init_hr_sensor();

  int periodo_muestreo = 10;
  int duracion_medida = 25000;
  timer_muestreo.setInterval(realizar_medidas, periodo_muestreo);
  timer_init_medida.setTimeout(iniciar_Medida, 5000);
  timer_duracion_medida.setTimeout(deshabilitarMedida,duracion_medida); //setTimeout para cuando lo llamemos una única vez.
}

void loop() {
  // put your main code here, to run repeatedly:
  timer_muestreo.handle();
  timer_init_medida.handle();
  timer_duracion_medida.handle();

}

void init_hr_sensor(){
  pinMode(D1,OUTPUT);
  pinMode(A0,INPUT);
  digitalWrite(D1, HIGH);
  fin_medida = false;
  init_medida = false;
  contador_pulsos = 0;
  primera_deteccion = true;
}

/**
 * Sería estupendo tener una forma de discriminar los primeros 5 segundos para no medir en ellos.
 */
void realizar_medidas(){
  if(!fin_medida && init_medida){
    tension_entrada = analogRead(A0); //Valor entre 0 y 1024.
    if(tension_entrada > umbral_deteccion){
      if(primera_deteccion){
        contador_pulsos++;
        primera_deteccion = false;
        Serial.println("PULSO");
        Serial.println("Contador pulsos");
        Serial.print(contador_pulsos);
        Serial.println("");
      }
    }else{
      primera_deteccion = true;
    }    
  }else{
    Serial.println("FIN DEL TIEMPO DE MEDIDA");
  }

}


void switch_off_hr_sensor(){
  digitalWrite(D1, LOW);
  init_medida = false;
}

void deshabilitarMedida(){
  fin_medida = true;
}

void iniciar_Medida(){
  init_medida = true;
}
