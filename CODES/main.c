#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "DIO_private.h"





 int main()
 {

u8 Button_Pressed;


RGBLED_init();   //active port F --> leds 

PushButtonInit();   //active port F --> switch
 


Button_Pressed=Sw_Input ();

 Is_Sw_Pressed(Button_Pressed );



 }









    
 