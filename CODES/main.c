#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "interface.h"

bool FixRecieved = 0;
char RecievedSentence[100] = {0};

char arr[100];

char lon[100], lat[100];
char Local_u8ReceivedChar;

int main()
{
	uart2_init();
	uart5_init();
	systick_init();
	PORTF_Initial();

	while(1){

		
		if(chk_start()) {
			uart5_send_string(lon);
			uart5_send('\n');
			uart5_send_string(lat);
      uart5_send('\n');
		}
                  
	

		delay(1);
	}

}
