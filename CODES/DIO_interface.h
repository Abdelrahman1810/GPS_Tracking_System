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

/* Macros for UART */
#define UART0           0
#define UART1           1
#define UART2           2
#define UART3           3
#define UART4           4
#define UART5           5
#define UART6           6
#define UART7           7

// define High and low
#define DIO_u8_HIGH     1
#define DIO_u8_LOW      0

/* DIO functions */
u8 DIO_u8SetPinDirection   (u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection);		//Saad
  
u8 DIO_u8SetPinValue 	   (u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue);			//Abdelrahman
  
u8 DIO_u8GetPinValue	   (u8 copy_u8PortId, u8 copy_u8PinId, u8 *copy_pu8ReturnedPinValue);	//Orabi
  
u8 DIO_u8SetPortDirection  (u8 copy_u8PortId, u8 copy_u8PortDirection);						    //Eman

u8 DIO_u8SetPortValue	   (u8 copy_u8PortId, u8 copy_u8PortValue);							    //Sarah
  
u8 DIO_u8GetPortValue	   (u8 copy_u8PortId, u8 *copy_u8ReturnedPortValue);					//Engy

/* UART functions */
u8 UART_u8ReadChar          (u8 copy_u8UARTNum);

void UART_ReadStr         (u8 copy_u8UARTNum, u8 *copy_pu8GPSData);

#endif