#include "BetaFit_Hardware.h"

#include "BetaFit_OLED_Module.h"

#include "buttonHandler.h"

#include "BetaFit_Definitions.h"

uint8_t mode;
void setup()
{

  mode = BETAFIT_MODE_INIT;

  OLED_Device_Begin( );

	buttonStart( );

  OLED_Device_Diplay_Menu_Item(mode);

  delay(1500);
}

void loop()
{
  buttonStateMachine( );

  if ( BUTTON_SHORT_PULSE_FLAG ) {

    BUTTON_SHORT_PULSE_FLAG = false;

    if (mode == 0x05) mode = BETAFIT_MODE_CLOCK;
    else mode = mode + 1;

    OLED_Device_Diplay_Menu_Item(mode);

  }

}