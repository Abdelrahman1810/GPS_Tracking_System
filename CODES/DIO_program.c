#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "STD_TYPES.h"
#include "tm4c123gh6pm.h"

u8 DIO_u8SetPinDirection 	(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection)
{
	if (copy_u8PinId >= DIO_u8_PIN_0 && copy_u8PinId <= DIO_u8_PIN_7) //Check if pin number is valid
	{
		switch (copy_u8PortId)
		{
		case DIO_u8PORTA:
			SET_BIT(SYSCTL_SCGCGPIO_R, SYSCTL_RCGCGPIO_R0) // Enable port clock
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

		case DIO_u8PORTB:
			break;
		case DIO_u8PORTC:
			break;
		case DIO_u8PORTD:
			break;
		case DIO_u8PORTE:
			break;
		case DIO_u8PORTF:
			break;
		default:
			return STD_TYPES_NOK; // Invalid port
		}
		return STD_TYPES_OK; // No errors
	}
	else
		return STD_TYPES_NOK; // Invalid pin number
}

u8_t DIO_u8_tSetPinValue 		(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue);

u8_t DIO_u8_tGetPinValue		(u8 copy_u8PortId, u8 copy_u8PinId, u8 *copy_pu8ReturnedPinValue);

u8_t DIO_u8_tSetPortDirection 	(u8 copy_u8PortId, u8 copy_u8PortDirection);

u8_t DIO_u8_tSetPortValue		(u8 copy_u8PortIa, u8 copy_u8PortValue);

u8_t DIO_u8_tGetPortValue		(u8 copy_u8PortId, u8 *copy_u8ReturnedPortValue);