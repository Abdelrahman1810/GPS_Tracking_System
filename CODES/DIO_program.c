#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "STD_TYPES.h"
#include "tm4c123gh6pm.h"

//void isCLKWork(u32 SYSCTL_PRGPIO) {
//	if (!GET_BIT(SYSCTL_PRGPIO_R, SYSCTL_PRGPIO))
//	{
//		SET_BIT(SYSCTL_SCGCGPIO_R, SYSCTL_PRGPIO); // Enable port clock
//		while (!GET_BIT(SYSCTL_PRGPIO_R, SYSCTL_PRGPIO)); // Wait till enabled
//	}
//	return;
//}

//Amr
void UART0_Write(u8 data){
	while((UART0_FR_R & 0X0020) != 0); //check if the FIFO is full
	UART0_DR_R = data;
}

//Amr
void UART1_Write(u8 data){
	while((UART1_FR_R & 0X0020) != 0); //check if the FIFO is full
	UART1_DR_R = data;
}


// Saad
u8 DIO_u8SetPinDirection (u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection) {
	if (copy_u8PinId >= DIO_u8_PIN_0 && copy_u8PinId <= DIO_u8_PIN_7) //Check if pin number is valid
	{
		switch (copy_u8PortId)
		{
		case DIO_u8PORT_A:
			SET_BIT(SYSCTL_SCGCGPIO_R, SYSCTL_RCGCGPIO_R0); // Enable port clock
			while (!GET_BIT(SYSCTL_PRGPIO_R, SYSCTL_PRGPIO_R0)); // Wait till enabled
			switch (copy_u8PinDirection)
			{
			case DIO_u8_INPUT:
				CLR_BIT(GPIO_PORTA_DIR_R, copy_u8PinId);
				break;

			case DIO_u8_OUTPUT:
				SET_BIT(GPIO_PORTA_DIR_R, copy_u8PinId);
				break;
			default:
				return STD_TYPES_NOK; // Invalid direction
			}
			break;

		case DIO_u8PORT_B:
			break;
		case DIO_u8PORT_C:
			break;
		case DIO_u8PORT_D:
			break;
		case DIO_u8PORT_E:
			break;
		case DIO_u8PORT_F:
			break;
		default:
			return STD_TYPES_NOK; // Invalid port
		}
		return STD_TYPES_OK; // No errors
	}
	else
		return STD_TYPES_NOK; // Invalid pin number
}

// Abdelrahman
u8 DIO_u8SetPinValue (u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue) {
	//Check if pin number and port name is valid
	if (  (copy_u8PinId >= DIO_u8_PIN_0 && copy_u8PinId <= DIO_u8_PIN_7) 
		&&(copy_u8PortId <= DIO_u8PORT_F && copy_u8PortId>=DIO_u8PORT_A))
	{
		switch (copy_u8PortId)
		{
		case DIO_u8PORT_A:
			SET_BIT(SYSCTL_SCGCGPIO_R, SYSCTL_RCGCGPIO_R0); // Enable port clock
			while (!GET_BIT(SYSCTL_PRGPIO_R, SYSCTL_PRGPIO_R0)); // Wait till enabled
			
			switch (copy_u8PinValue)
			{
			case DIO_u8_HIGH:
				SET_BIT(GPIO_PORTA_DATA_R, copy_u8PinId);
				break;
			case DIO_u8_LOW:
				CLR_BIT(GPIO_PORTA_DATA_R, copy_u8PinId);
				break;
			default:
				return STD_TYPES_NOK; // Invalid direction
			}
			break;
		case DIO_u8PORT_F:
			SET_BIT(SYSCTL_SCGCGPIO_R, SYSCTL_RCGCGPIO_R5); // Enable port clock
			while (!GET_BIT(SYSCTL_PRGPIO_R, SYSCTL_RCGCGPIO_R5)); // Wait till enabled
			
			switch (copy_u8PinValue)
			{
			case DIO_u8_HIGH:
				SET_BIT(GPIO_PORTF_DATA_R, copy_u8PinId);
				break;
			case DIO_u8_LOW:
				CLR_BIT(GPIO_PORTF_DATA_R, copy_u8PinId);
				break;
			default:
				return STD_TYPES_NOK; // Invalid direction
			}
			break;
		default:
			return STD_TYPES_NOK; // Invalid Value
		}
	}
	else
		return STD_TYPES_NOK; // Invalid 
	return STD_TYPES_OK; // Mission Done
}

// Oraby
u8 DIO_u8GetPinValue (u8 copy_u8PortId, u8 copy_u8PinId, u8 *copy_pu8ReturnedPinValue) {
   if((copy_pu8ReturnedPinValue != NULL)
   		&&(copy_u8PortId <= DIO_u8PORT_F && copy_u8PortId>=DIO_u8PORT_A)
		&&(copy_u8PinId  >= DIO_u8_PIN_0 && copy_u8PinId<=DIO_u8_PIN_7)) {
		switch(copy_u8PortId)
		{
			case DIO_u8PORT_A:
				SET_BIT(SYSCTL_SCGCGPIO_R, SYSCTL_RCGCGPIO_R0); // Enable port clock
				while (!GET_BIT(SYSCTL_PRGPIO_R, SYSCTL_PRGPIO_R0)); // Wait till enabled
				
				*copy_pu8ReturnedPinValue = GET_BIT(GPIO_PORTA_DATA_R,copy_u8PinId);
				
				switch(*copy_pu8ReturnedPinValue) {
					case DIO_u8_HIGH:
						*copy_pu8ReturnedPinValue = DIO_u8_HIGH;
						break;
					case DIO_u8_LOW :
						*copy_pu8ReturnedPinValue = DIO_u8_LOW;
						break;
					default:
						return STD_TYPES_NOK; // Invalid Value
				}
			break;

		case DIO_u8PORT_B:
			break;
		case DIO_u8PORT_C:
			break;
		case DIO_u8PORT_D:
			break;
		case DIO_u8PORT_E:
			break;
		case DIO_u8PORT_F:
			break;
		default:
			return STD_TYPES_NOK; // Invalid port
		}
	}
	else
	return STD_TYPES_NOK;
}

u8 DIO_u8SetPortDirection 	(u8 copy_u8PortId, u8 copy_u8PortDirection);
//Sarah 

u8 DIO_u8SetPortValue		(u8 copy_u8PortIa, u8 copy_u8PortValue){
	switch(copy_u8PortId)
	{

		case DIO_u8PORTA:
		GPIO_PORTA_DATA_R=copy_u8PortValue;
		break;
		case DIO_u8PORTB:
		GPIO_PORTB_DATA_R=copy_u8PortValue;
		break;
		case DIO_u8PORTC:
		GPIO_PORTC_DATA_R=copy_u8PortValue;
		break;
		case DIO_u8PORTD:
		GPIO_PORTD_DATA_R=copy_u8PortValue;
		break;
		case DIO_u8PORTE:
		GPIO_PORTE_DATA_R=copy_u8PortValue;
		break;
		case DIO_u8PORTF:
		GPIO_PORTF_DATA_R=copy_u8PortValue;
		break;
		default: //invalid port
		return SYD_TYPES_NOK;
		break;
		return SYD_TYPES_OK;
	}
}

//Engy
u8 DIO_u8GetPortValue		(u8 copy_u8PortId, u8 *copy_u8ReturnedPortValue)
{
     if(copy_u8ReturnedPortValue != NULL && ((copy_u8PortId >=DIO_u8PORT_A)&&(copy_u8PortId <=DIO_u8PORT_F)))
    {
        switch (copy_u8PortId)
        {
            case DIO_u8PORT_A:*copy_u8ReturnedPortValue = GPIO_PORTA_DATA_R;
            break;
             case DIO_u8PORT_B:*copy_u8ReturnedPortValue = GPIO_PORTB_DATA_R;
            break;
             case DIO_u8PORT_C:*copy_u8ReturnedPortValue = GPIO_PORTC_DATA_R;
            break;
             case DIO_u8PORT_D:*copy_u8ReturnedPortValue = GPIO_PORTD_DATA_R;
            break;
             case DIO_u8PORT_E:*copy_u8ReturnedPortValue = GPIO_PORTE_DATA_R;
            break;
             case DIO_u8PORT_F:*copy_u8ReturnedPortValue = GPIO_PORTF_DATA_R;
            break;
             default:
                return STD_TYPES_NOK; //if there is error
        }
        return STD_TYPES_OK;
    }
    else
    {
        return STD_TYPES_NOK;
    }
}

