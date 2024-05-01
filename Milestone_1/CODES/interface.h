#ifndef __INTERFACE_C__H
#define __INTERFACE_C__H
#include "STD_TYPES.h"

/* Macros for PORTS */
#define u8PORT_A 	0
#define u8PORT_B 	1
#define u8PORT_C 	2
#define u8PORT_D 	3
#define u8PORT_E 	4
#define u8PORT_F 	5

/* Macros for PINS */
#define u8_PIN_0 	0
#define u8_PIN_1 	1
#define u8_PIN_2	2
#define u8_PIN_3 	3
#define u8_PIN_4 	4
#define u8_PIN_5 	5
#define u8_PIN_6 	6
#define u8_PIN_7 	7

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
#define u8_HIGH     1
#define u8_LOW      0

/* DIO functions */
void RGBLED_init(void) ;

void PushButtonInit(void);

u8  Sw_Input (void);

void Is_Sw_Pressed(u8 SW2);



/* UART functions */
u8 UART_u8ReadChar(u8 copy_u8UARTNum);

void UART_ReadStr(u8 copy_u8UARTNum, u8 *copy_pu8GPSData);

void UART0_Init(void);

void UART1_Init(void);

void UART0_Write(u8 data);

void UART1_Write(u8 data);

/*GPS FUNCTIONS */
void APP_voidGetDistance(f32 copy_f32startLatitude, f32 copy_f32startLongitude,f32 copy_f32endLatitude, f32 copy_f32endLongitude, f32 *copy_pf32distance);

#endif
