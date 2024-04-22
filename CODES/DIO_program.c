

u8_t DIO_u8_tSetPinDirection 	(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection)
{
	switch(copy_u8PortId)
	{
		case DIO_u8PORTA:
			SET_BIT (SYSCTL_SCGCGPIO_R, SYSCTL_RCGCGPIO_R0)
			while(GET_BIT (SYSCTL_PRGPIO_R, SYSCTL_PRGPIO_R0) == 0);
			switch(copy_u8PinDirection)
			{
				case DIO_u8_OUTPUT: SET_BIT (REG, BIT_NUMBER);
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
	}
}

u8_t DIO_u8_tSetPinValue 		(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue);

u8_t DIO_u8_tGetPinValue		(u8 copy_u8PortId, u8 copy_u8PinId, u8 *copy_pu8ReturnedPinValue);

u8_t DIO_u8_tSetPortDirection 	(u8 copy_u8PortId, u8 copy_u8PortDirection);

u8_t DIO_u8_tSetPortValue		(u8 copy_u8PortIa, u8 copy_u8PortValue);

u8_t DIO_u8_tGetPortValue		(u8 copy_u8PortId, u8 *copy_u8ReturnedPortValue);