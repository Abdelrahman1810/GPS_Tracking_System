#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "STD_TYPES.h"
#include "interface.h"

void uart2_init();
void uart2_send(uint8_t character);
void uart2_send_string(char * string);
char uart2_receive();
void uart2_receive_string(char * string, uint32_t len);
void uart5_init();
void uart5_send(uint8_t character);
void uart5_send_string(char * string);
char uart5_receive();
void uart5_receive_string(char * string, uint32_t len); 

///////////////////////////////////////////////
//    MOHAMAD SAAD M.HASSAN MULKI 2101894	 //
///////////////////////////////////////////////


///////////////////////////////////////////////
//    EMAN SHERIF SAYED RAGHEB 2100721		 //
///////////////////////////////////////////////
