#include "STD_TYPES.h"
#include "interface.h"
#include "private.h"

int main() {
    
    u8 Button_Pressed;

    RGBLED_init();   //active port F --> leds 

    PushButtonInit();   //active port F --> switch
	
		while(1) Is_Sw_Pressed(Button_Pressed);
}
