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


///////////////////////////////////////////////
//    Amr Ayman Mohamed Abdo 2100374	     //
///////////////////////////////////////////////
