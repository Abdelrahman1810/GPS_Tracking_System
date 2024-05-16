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
bool get_cordinates() {    //  073802.00,3003.90540,N,03116.79589,E,1,06,1.48,32.4,M,15.4,M,,*6B
   
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
bool chk_FIX() {
    Local_u8ReceivedChar = uart2_receive();
    if (Local_u8ReceivedChar == '1')
        return 1;
    return 0;
}

bool GPS_voidReceiveSentence( char *Local_u8GPS_Sentence )   
{
   
    u8 Local_u8ReadCounter  = 0;
    u8 comma_count = 0;
    u8 Local_u8GPS_Check_Index=0;
    u8 Local_u8GPS_Check[] = "$GPGGA,";
    u8 Local_u8ReceivedChar;
    

    while (Local_u8GPS_Check_Index<7)      // Check if the recived nmea sentence is correct should start with "$GPGGA,"
    {
                    Local_u8ReceivedChar=uart2_receive();
        if(Local_u8ReceivedChar==Local_u8GPS_Check[Local_u8GPS_Check_Index])
                    Local_u8GPS_Check_Index++; 

        else return 0; // return 0 if there is only one difference between the recived sentence and check sentence
    } 

    while(Local_u8ReceivedChar != '*')  // If we come here that means we recived the correct nmea sentence then we well take the whole sentence 
    {   
      Local_u8ReceivedChar=uart2_receive();
      Local_u8GPS_Sentence[Local_u8ReadCounter] = Local_u8ReceivedChar;
      Local_u8ReadCounter++;
    }

    while (*Local_u8GPS_Sentence != '*')  // Find fix value ---> the desired value is 1 nothing else
    {
       
     if (*Local_u8GPS_Sentence == ',') 
     {
            comma_count++;
           
        if (comma_count == 5)   // The comma after which we can find the fix value
        {
            if (*(Local_u8GPS_Sentence + 1) == '1') 
                  return 1;   // correct fix 

            else  return 0;   // wrong fix 

                
        }
     }
    
        Local_u8GPS_Sentence++; 
    }

}

///////////////////////////////////////////////
//    Amr Ayman Mohamed Abdo 2100374	     //
///////////////////////////////////////////////

f32 truncate(f32 *copy_f32FloatValue)
{
    *copy_f32FloatValue = floor(*copy_f32FloatValue * 10000) / (f64)10000.0;
    return *copy_f32FloatValue;
}

void APP_voidGetDistance(f32 copy_f32startLatitude, f32 copy_f32startLongitude,f32 copy_f32endLatitude, f32 copy_f32endLongitude, f32 *copy_pf32distance)
{
    // convert all coordinates from Degrees into Radians
    f32 Local_f32startLat = truncate(&copy_f32startLatitude)* M_PI/180;
    f32 Local_f32startLong = truncate(&copy_f32startLongitude)* M_PI/180;
    f32 Local_f32endLat = truncate(&copy_f32endLatitude)* M_PI/180;
    f32 Local_f32endLong = truncate(&copy_f32endLongitude)* M_PI/180;

    // calculate latitude difference and longitude difference
    f32 Local_f32latDifference = Local_f32endLat - Local_f32startLat;
    f32 Local_f32longDifference = Local_f32endLong - Local_f32startLong;

    //use Haversine formula
    f32 Local_f32a = sin(Local_f32latDifference / 2) * sin(Local_f32latDifference / 2) + cos(Local_f32startLat) * cos(Local_f32endLat)
    * sin(Local_f32longDifference / 2) * sin(Local_f32longDifference / 2);
    f32 Local_f32c = 2 * atan2(sqrt(Local_f32a), sqrt(1 - Local_f32a));

    //Multipy by Earth's Radius to get the distance
    *copy_pf32distance = Local_f32c * Earth_Radius;
}



void GPS_voidExtractCoordinates(u8 *copy_pu8Sentence, u8 *copy_u8Longitude,u8 *copy_u8Latitude )
{
    
    u8 i = 0, j = 0;
    
   while (copy_pu8Sentence[i] != ',' )    		// Find the first comma
    {
        i++;
    }

    i++;                                      	//jump just after the next comma

   while (copy_pu8Sentence[i] != ',' )      	//Extract longitude until the next comma
    {
        copy_u8Longitude[j++] = copy_pu8Sentence[i++];
    }
        copy_u8Longitude[j] = '\0';             //Null-terminate the string
   
    i+=3;                                     //jump just after the next comma
    j=0;                                     // Reset j for latitude array
    
    while (copy_pu8Sentence[i] != ',')       // Extract latitude until the next comma
    {
        copy_u8Latitude[j++] = copy_pu8Sentence[i++];
    }
        copy_u8Latitude[j] = '\0';                  // Null-terminate the string
   
}
