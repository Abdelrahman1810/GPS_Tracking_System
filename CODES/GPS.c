#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "STD_TYPES.h"
#include "interface.h"
#define M_PI 3.1415926
#define Earth_Radius 6371000

bool GPS_voidReceiveSentence( char *Local_u8GPS_Sentence );
f32 truncate(f32 *copy_f32FloatValue);
void APP_voidGetDistance(f32 copy_f32startLatitude, f32 copy_f32startLongitude,f32 copy_f32endLatitude, f32 copy_f32endLongitude, f32 *copy_pf32distance);
void GPS_voidExtractCoordinates(u8 *copy_pu8Sentence, u8 *copy_u8Longitude,u8 *copy_u8Latitude );
char lon[100], lat[100];
char Local_u8ReceivedChar;

///////////////////////////////////////////////
//    Mohamed Magdi Mohamed Ahmed 2100519    //
///////////////////////////////////////////////

bool chk_start() {
   
    u8 Local_u8GPS_Check[] = "GPGGA,";
    
    Local_u8ReceivedChar=uart2_receive();    
    if(Local_u8ReceivedChar=='$') {
        char arr[6];
        int i;
        for ( i = 0; i < 6; i++)
        {
            Local_u8ReceivedChar=uart2_receive();
            arr[i] = Local_u8ReceivedChar;
        }
        if (!strcmp(arr, Local_u8GPS_Check))
        {
            return get_cordinates();
        }
        else 
            return 0;
    }
    else 
        return 0;
}

bool chk_FIX() {
    Local_u8ReceivedChar = uart2_receive();
    if (Local_u8ReceivedChar == '1')
        return 1;
    return 0;
}

///////////////////////////////////////////////
//    Amr Ayman Mohamed Abdo 2100374	     //
///////////////////////////////////////////////

bool get_cordinates() {    //073802.00,3003.90540,N,03116.79589,E,1,06,1.48,32.4,M,15.4,M,,*6B
   
    while (uart2_receive() != ','); //skip till 1st comma after it we will take the longitude ---> skip this (073802.00)
    int i = 0;
    Local_u8ReceivedChar = uart2_receive();
    while (Local_u8ReceivedChar != ','){
        lon[i++] = Local_u8ReceivedChar;     //stores the longitude
        Local_u8ReceivedChar = uart2_receive();
    }

    while (uart2_receive() != ',');  //skip till 3rd comma after it we will take the latitide 

    i = 0;
    Local_u8ReceivedChar = uart2_receive();
    while (Local_u8ReceivedChar != ','){
        lat[i++] = Local_u8ReceivedChar;      //skip till 5th comma after it we will check fix      
        Local_u8ReceivedChar = uart2_receive();
    }
    while (uart2_receive() != ',');
    return chk_FIX();
}