#include "src/buttonHandler/buttonHandler.h"

void setup(void) {
  Serial.begin(9600);

  //Solo se llama una vez en el setup
  buttonStart();
}


void loop(void) {

  //Para que funcione bien el módulo hay que llamarlo en cada iteración en el loop
  buttonStateMachine();


  //Las dos flags para las pulsaciones corta y larga. Se tienen que poner a false desde fuera del módulo.
  //Otra cosa a tener en cuenta es que la pulsación corta se dispara cuando se deja de pulsar pero la pulsacion
  //larga de dispara cuando pasa el tiempo de pulsacion larga, independientemente de que se haya dejado de pulsar o no.
  if(BUTTON_SHORT_PULSE_FLAG){
    BUTTON_SHORT_PULSE_FLAG = false;
    Serial.println("Pulsación corta");
  }
  if(BUTTON_LONG_PULSE_FLAG){
    BUTTON_LONG_PULSE_FLAG = false;
    Serial.println("Pulsación larga");
  }
}
