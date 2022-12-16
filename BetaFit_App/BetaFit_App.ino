// Include main module.
#include "../Main/BetaFit_Main_Module.h"

void setup() {
  Serial.begin(115200);

  BetaFit_Setup( );

}

void loop() {
  BetaFit_Main( );
}
