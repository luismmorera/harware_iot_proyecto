#define BetaFit_Debug_Mode

#include "src/BetaFit_Debug_Options.h"

// Include main module.
#include "src/Main/BetaFit_Main_Module.h"

void setup() {
  Serial.begin(115200);
  BetaFit_Setup( );
}

void loop() {
  BetaFit_Main( );
}
