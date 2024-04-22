#ifndef __DIO_INTERFACE_C__H
#define __DIO_INTERFACE_C__H

/* Macros for PORTS */
#define DIO_u8PORT_A 	0
#define DIO_u8PORT_B 	1
#define DIO_u8PORT_C 	2
#define DIO_u8PORT_D 	3
#define DIO_u8PORT_E 	4
#define DIO_u8PORT_F 	5

/* Macros for PINS */
#define DIO_u8_PIN_0 	0
#define DIO_u8_PIN_1 	1
#define DIO_u8_PIN_2	2
#define DIO_u8_PIN_3 	3
#define DIO_u8_PIN_4 	4
#define DIO_u8_PIN_5 	5
#define DIO_u8_PIN_6 	6
#define DIO_u8_PIN_7 	7


// define High and low
#define DIO_u8_HIGH     1
#define DIO_u8_LOW      0


u8_t DIO_u8_tSetPinDirection   (u8_t copy_u8PortId, u8_t copy_u8PinId, u8_t copy_u8PinDirection);		//Saad
  
u8_t DIO_u8_tSetPinValue 	   (u8_t copy_u8PortId, u8_t copy_u8PinId, u8_t copy_u8PinValue);			//Abdelrahman
  
u8_t DIO_u8_tGetPinValue	   (u8_t copy_u8PortId, u8_t copy_u8PinId, u8_t *copy_pu8ReturnedPinValue);	//Orabi
  
u8_t DIO_u8_tSetPortDirection  (u8_t copy_u8PortId, u8_t copy_u8PortDirection);						    //Eman

u8_t DIO_u8_tSetPortValue	   (u8_t copy_u8PortId, u8_t copy_u8PortValue);							    //Sarah
  
u8_t DIO_u8_tGetPortValue	   (u8_t copy_u8PortId, u8_t *copy_u8ReturnedPortValue);					//Engy



#endif