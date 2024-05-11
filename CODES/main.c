#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"


int main() {


         RGBLED_init();   
         PushButtonInit();   
         UART0_Init();
         UART1_Init();

         
   
   
   while (1)
   {           
         u8 Fix_Flag=0;
         u8 Recive_Sentence[100]={0};
         u8 longitude_U8[15]={0};
         u8 latitude_U8[15]={0};
             
         do {  Fix_Flag= GPS_voidReceiveSentence(Recive_Sentence); } while (Fix_Flag==0);

           
               GPS_voidExtractCoordinates(Recive_Sentence, longitude_U8, latitude_U8);


               Send_Data(longitude_U8,latitude_U8);
}
   



    
    u8 Button_Pressed;

    RGBLED_init();   //active port F --> leds 

    PushButtonInit();   //active port F --> switch

    Button_Pressed=Sw_Input ();

    Is_Sw_Pressed(Button_Pressed );
}