#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "interface.h"

void systick_init(void);
void wait_1ms(void);
void delay(int t);

///////////////////////////////////////////////
//    	  Engy khaled sayed 2100610			 //
///////////////////////////////////////////////    
void systick_init(void) {

    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = 0x00FFFFFF;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0x05;
}

void wait_1ms(void) {

    NVIC_ST_RELOAD_R = 16000 - 1;
    NVIC_ST_CURRENT_R = 0;
    while ((NVIC_ST_CTRL_R & 0x00010000) == 0);
}

void delay(int t) {

    int i = 0;
    for (i=0; i < t; i++)
        wait_1ms();
}
