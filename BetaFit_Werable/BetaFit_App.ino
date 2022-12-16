// Include main module.
#include "src/Main/BetaFit_Main_Module.h"

#include "src/BetaFit_Debug_Options.h"

#define BetaFit_Debug_Mode

void setup() {
  Serial.begin(115200);

  BetaFit_Setup( );

}

void loop() {
  BetaFit_Main( );
}
