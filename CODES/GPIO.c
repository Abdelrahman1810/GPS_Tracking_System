#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "STD_TYPES.h"
#include "interface.h"

void GPIOF_Handler(void);
void PORTF_Initial(void);
void RGB_SetOutput(unsigned char data);
void RGB_ClearOutput(unsigned char data);
void RGB_ToggleOutput(void);

///////////////////////////////////////////////
//    Sarah Hamed Mahmoud Alsayed 2101518    //
///////////////////////////////////////////////
