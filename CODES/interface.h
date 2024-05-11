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

/* Masks */
#define PF_mask 0x20
#define PF0_mask 0x01

/* DIO functions */
void RGBLED_init(void) ;

void PushButtonInit(void);

u8  Sw_Input (void);

void Is_Sw_Pressed(u8 SW2);

u8 u8SetPinDirection   (u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection);		//Saad
  
u8 u8SetPinValue 	   (u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue);			//Abdelrahman
  
u8 u8GetPinValue	   (u8 copy_u8PortId, u8 copy_u8PinId, u8 *copy_pu8ReturnedPinValue);	//Orabi
  
u8 u8SetPortDirection  (u8 copy_u8PortId, u8 copy_u8PortDirection);						    //Eman

u8 u8SetPortValue	   (u8 copy_u8PortId, u8 copy_u8PortValue);							    //Sarah
  
u8 u8GetPortValue	   (u8 copy_u8PortId, u8 *copy_u8ReturnedPortValue);					//Engy

/* UART functions */


void UART0_Init(void);

void UART1_Init(void);

void UART0_Write(u8 data);

u8 UART0_Available(void);

u8 UART0_read(void);

void Send_Data(char *longitude ,char *lat);



/*GPS Functions */
u8 GPS_voidReceiveSentence( u8 *Local_u8GPS_Sentence ) ;
void GPS_voidExtractCoordinates(u8 *copy_pu8Sentence, u8 *copy_u8Longitude,u8 *copy_u8Latitude );
f32 truncate(f32 *copy_f32FloatValue);
void APP_voidGetDistance(f32 copy_f32startLatitude, f32 copy_f32startLongitude,f32 copy_f32endLatitude, f32 copy_f32endLongitude, f32 *copy_pf32distance);



/*Timer Functions*/
void SysTick_Init(u64 delay);
void SysTick_Wait(u64  delay);

#endif