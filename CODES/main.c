#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "STD_TYPES.h"
#include "interface.h"

bool FixRecieved = 0;
char RecievedSentence[100] = {0};
char lon[15];
char lat[15];

int main()
{
	uart2_init();
	uart5_init();
	systick_init();
	PORTF_Initial();

	while(1){

		FixRecieved = GPS_voidReceiveSentence(RecievedSentence);

		if(FixRecieved){
			GPS_voidExtractCoordinates(RecievedSentence, lon, lat);
			uart5_send_string(RecievedSentence);
		}

		delay(500);
	}

}