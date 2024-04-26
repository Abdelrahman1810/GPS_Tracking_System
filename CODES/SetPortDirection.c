#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "tm4c123gh6pm.h"
#include "DIO_private.h"
#include "DIO_interface.h"


		
u8 DIO_u8SetPortDirection(u8 copy_u8PortId, u8 copy_u8PortDirection ){
	if(copy_u8PortId>=DIO_u8_PORTA&&copy_u8PortId<=DIO_u8_PORTF)       //check if PortId is valid
	{
		SET_BIT(SYSCTL_RCGCGPIO_R,copy_u8PortId); 						// To enable a clock and active PORT A
		while(!GET_BIT(SYSCTL_PRGPIO_R,copy_u8PortId)); 			// Wait till the Clock be stable
		switch(copy_u8PortId)
		{
			case DIO_u8_PORTA:
				GPIO_PORTA_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTA_CR_R    = GPIO_ENABLE_7_BIT;						// Allow changes to PA7-0 
				GPIO_PORTA_AFSEL_R = 0x00;												// Disable analog functions
				GPIO_PORTA_PCTL_R  = GPIO_PCTL_VALUE; 						// GPIO_PCTL_VALUE-->To make all pins in PORT A work as DIO 
				GPIO_PORTA_DEN_R   = 0xFF;												// to enable pin PA0-PA7 as digital 
			break;
			case DIO_u8_PORTB:
				GPIO_PORTB_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTB_CR_R    = GPIO_ENABLE_7_BIT;						// Allow changes to PA7-0 
				GPIO_PORTB_AFSEL_R = 0x00;												// Disable the alternative functions
				GPIO_PORTB_PCTL_R  = GPIO_PCTL_VALUE; 						// GPIO_PCTL_VALUE-->To make all the pins in PORT B work as DIO 
				GPIO_PORTB_DEN_R   = 0xFF;												// to enable the pin PB0-PB7 as digital 
			break;
			case DIO_u8_PORTC:
				GPIO_PORTC_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTC_CR_R    = GPIO_ENABLE_7_BIT;						// Allow changes to PA7-0 
				GPIO_PORTC_AFSEL_R = 0x00;												// Disable the alternative functions
				GPIO_PORTC_PCTL_R  = GPIO_PCTL_VALUE; 						// GPIO_PCTL_VALUE-->To make all the pins in PORT C work as DIO  
				GPIO_PORTC_DEN_R   = 0xFF;												// to enable the pin PB0-PB7 as digital 
			break;
			case DIO_u8_PORTD:
				GPIO_PORTD_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTD_CR_R    = GPIO_ENABLE_7_BIT;						// Allow changes to PA7-0 
				GPIO_PORTD_AFSEL_R = 0x00;												// Disable the alternative functions
				GPIO_PORTD_PCTL_R  = GPIO_PCTL_VALUE; 						// GPIO_PCTL_VALUE-->To make all the pins in PORT D work as DIO
				GPIO_PORTD_DEN_R   = 0xFF;												// to enable the pin PD0-PD7 as digital 
			break;
			case DIO_u8_PORTE:
				GPIO_PORTE_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTE_CR_R    = GPIO_ENABLE_7_BIT;						// Allow changes to PA7-0 
				GPIO_PORTE_AFSEL_R = 0x00;												// Disable the alternative functions
				GPIO_PORTE_PCTL_R  = GPIO_PCTL_VALUE; 						// GPIO_PCTL_VALUE-->To make all the pins in PORT E work as DIO 
				GPIO_PORTE_DEN_R   = 0xFF;												// to enable the pin PE0-PE7 as digital 
			break;
			case DIO_u8_PORTF:
				GPIO_PORTF_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTF_CR_R    = GPIO_ENABLE_7_BIT;						// Allow changes to PA7-0 
				GPIO_PORTF_AFSEL_R = 0x00;												// Disable the alternative functions
				GPIO_PORTF_PCTL_R  = GPIO_PCTL_VALUE; 						// GPIO_PCTL_VALUE-->To make all the pins in PORT F work as DIO 
				GPIO_PORTF_DEN_R   = 0xFF;												// to enable the pin PF0-PF7 as digital 
			break;
			default 		  : return STD_TYPES_NOK; // PortId is Not valid
		}
	}
	else
		return STD_TYPES_NOK; // PortId is Not valid
	
   if ( copy_u8PortDirection==DIO_u8_OUTPUT||copy_u8PortDirection==DIO_u8_INPUT) // check if PortDirection is valid
   {
		switch(copy_u8PortId)
		{
			case DIO_u8PORT_A:
				switch(copy_u8PortDirection){
					case DIO_u8_INPUT: GPIO_PORTA_DIR_R=0x00; break;
					case DIO_u8_OUTPUT: GPIO_PORTA_DIR_R=0xFF; break;
					default: return STD_TYPES_NOK;
				}
				break;
			case DIO_u8PORT_B:
				switch(copy_u8PortDirection){
			    	case DIO_u8_INPUT: GPIO_PORTA_DIR_R=0x00; break;
					case DIO_u8_OUTPUT: GPIO_PORTA_DIR_R=0xFF; break;
					default: return STD_TYPES_NOK;
				}
				break;
			case DIO_u8PORT_C:
				switch(copy_u8PortDirection){
					case DIO_u8_INPUT: GPIO_PORTA_DIR_R=0x00; break;
					case DIO_u8_OUTPUT: GPIO_PORTA_DIR_R=0xFF; break;
					default: return STD_TYPES_NOK;
				}
				break;
			case DIO_u8PORT_D:
				switch(copy_u8PortDirection){
					case DIO_u8_INPUT: GPIO_PORTA_DIR_R=0x00; break;
					case DIO_u8_OUTPUT: GPIO_PORTA_DIR_R=0xFF; break;
					default: return STD_TYPES_NOK;
				}
				break;
			case DIO_u8PORT_E:
				switch(copy_u8PortDirection){
					case DIO_u8_INPUT: GPIO_PORTA_DIR_R=0x00; break;
					case DIO_u8_OUTPUT: GPIO_PORTA_DIR_R=0xFF; break;
					default: return STD_TYPES_NOK;
				}
				break;
			case DIO_u8PORT_F:
				switch(copy_u8PortDirection){
					case DIO_u8_INPUT: GPIO_PORTA_DIR_R=0x00; break;
					case DIO_u8_OUTPUT: GPIO_PORTA_DIR_R=0xFF; break;
					default: return STD_TYPES_NOK;
				}
				    break;
				    default: return STD_TYPES_NOK;
				}
				    return STD_TYPES_OK; // MISSION COMPLETE
				}
else
      return STD_TYPES_NOK;	// PortDirection is Not valid   
}
