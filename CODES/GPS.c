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


///////////////////////////////////////////////
//    Amr Ayman Mohamed Abdo 2100374	     //
///////////////////////////////////////////////
