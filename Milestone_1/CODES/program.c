#include "interface.h"
#include "private.h"
#include "STD_TYPES.h"
#include "tm4c123gh6pm.h"
#include "BIT_MATH.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//////////////////////////////////
//	Engy Khaled Sayed 2100610	//
//////////////////////////////////
void RGBLED_init(void){
	SET_BIT(SYSCTL_RCGCGPIO_R,SYSCTL_PRGPIO_R5); //clock of portf
	while((SYSCTL_PRGPIO_R & PF_mask)==0);
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTF_CR_R |= PF123_mask;
	GPIO_PORTF_AFSEL_R &= ~PF123_mask;
	GPIO_PORTF_AMSEL_R &= ~PF123_mask;
	GPIO_PORTF_PCTL_R &= ~0x0000FFF0; //clear bits
	GPIO_PORTF_DIR_R  |= PF123_mask; //Leds are output
	GPIO_PORTF_DEN_R  |= PF123_mask;
	GPIO_PORTF_DATA_R &= ~PF123_mask;
}

//////////////////////////////////////////
//	Sarah Hamed Mahmoud Alsayed 2101518	//
//////////////////////////////////////////
void PushButtonInit(){
	SET_BIT(SYSCTL_RCGCGPIO_R,SYSCTL_PRGPIO_R5); //configure clk for portf
	while((SYSCTL_PRGPIO_R&PF_mask)==0);
	GPIO_PORTF_LOCK_R= GPIO_LOCK_KEY;
	GPIO_PORTF_CR_R |=PF0_mask;
	GPIO_PORTF_AMSEL_R &= ~PF0_mask;
	GPIO_PORTF_AFSEL_R &= ~PF0_mask;
	GPIO_PORTF_PCTL_R &= ~0x0000000f; //clear bits in ptcl
	GPIO_PORTF_DIR_R &= ~PF0_mask; // set buttons as output pins
	GPIO_PORTF_DEN_R |=PF0_mask; //enable digital i/o
	GPIO_PORTF_PUR_R = PF0_mask;
} 

///////////////////////////////////////////////
//    Mohamed Magdi Mohamed Ahmed 2100519    //
///////////////////////////////////////////////
// switch input
u8  Sw_Input (void)
{
	return GPIO_PORTF_DATA_R & 0x01;
}

//LEDs Output
void LEDs_Output (u8 data)
{
	GPIO_PORTF_DATA_R &= ~PF123_mask;
	GPIO_PORTF_DATA_R|= data;
}

void Is_Sw_Pressed(u8 SW2)
{   
	SW2 = Sw_Input();
	if (!SW2/* && distance >= 100*/)
		LEDs_Output (RED);
}


/* UART functions */
// Baud Rate=9600 bits/sec 
// 16 MHz System Clock  , ClkDivision=16

///////////////////////////////////////////////
//		Eman Sherif Sayed Ragheb 2100721     // 
///////////////////////////////////////////////
void UART0_Init(void){
	SYSCTL_RCGCUART_R |=SYSCTL_RCGCUART_R0;  // Activate UART0
	SYSCTL_RCGCGPIO_R |=SYSCTL_RCGCGPIO_R0; // Activate PORTA
	UART1_CTL_R &= ~UART_CTL_UARTEN; // disable UART0
	UART1_IBRD_R = 104; // IBRD=int(16000000 /9600*16)=int(104.166667)
	UART1_FBRD_R = 11; // FBRD=int(0.166667*64 + 0.5)
	UART1_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN); // 8-bit word length ,enable FIFO
	UART1_CTL_R &= (UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE); // enable RXE ,TXE ,UART0
	GPIO_PORTA_AFSEL_R |=0x03; // enable Alternate func PA0,PA1
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & ~0xFF) | (GPIO_PCTL_PA0_U0RX | GPIO_PCTL_PA1_U0TX); // configure UART for PA0, PA1
	GPIO_PORTA_DEN_R |= 0x03; // enable digitai i/o for PA0 ,PA1
	GPIO_PORTA_AMSEL_R &= ~0x03; } // disable analog func for PA0 ,PA1\
	
///////////////////////////////////////////////
//		Eman Sherif Sayed Ragheb 2100721     // 
///////////////////////////////////////////////
void UART1_Init(void){
	SYSCTL_RCGCUART_R |=SYSCTL_RCGCUART_R1; // Activate UART1
	SYSCTL_RCGCGPIO_R |=SYSCTL_RCGCGPIO_R1; // Activate PORTB
	UART1_CTL_R &= ~UART_CTL_UARTEN; // disable UART1
	UART1_IBRD_R = 104; // IBRD=int(16000000 /9600*16)=int(104.166667)
	UART1_FBRD_R = 11; // FBRD=int(0.166667*64 + 0.5)
	UART1_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN); // 8-bit word length ,enable FIFO
	UART1_CTL_R &= (UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE); // enable RXE ,TXE ,UART1
	GPIO_PORTB_AFSEL_R |=0x03; // enable Alternate func PB0,PB1
	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & ~0xFF) | (GPIO_PCTL_PB0_U1RX | GPIO_PCTL_PB1_U1TX); // configure UART for PB0, PB1
	GPIO_PORTB_DEN_R |= 0x03; // enable digitai i/o for PB0 ,PB1
	GPIO_PORTB_AMSEL_R &= ~0x03; // disable analog func for PB0 ,PB1 
}

///////////////////////////////////////////////
//		Amr Ayman Mohamed Abdo 2100374 		 //
///////////////////////////////////////////////
void UART0_Write(u8 data){
	while((UART0_FR_R & 0X0020) != 0); //check if the FIFO is full
	UART0_DR_R = data;
}

///////////////////////////////////////////////
//		Amr Ayman Mohamed Abdo 2100374 		 //
///////////////////////////////////////////////
void UART1_Write(u8 data){
	while((UART1_FR_R & 0X0020) != 0); //check if the FIFO is full
	UART1_DR_R = data;
}

//////////////////////////////////////////////
//	MOHAMAD SAAD M. HASSAN MULKI 2101894	//
//////////////////////////////////////////////
u8 UART_u8ReadChar(u8 copy_u8UARTNum){
    switch(copy_u8UARTNum){
        case UART0:
        while(UART1_FR_R & UART_FR_RXFE);
        return UART0_DR_R & 0xFF;
        case UART1:
        while(UART1_FR_R & UART_FR_RXFE);
        return UART1_DR_R & 0xFF;

        case UART2:
        //while(UART2_FR_R & UART_FR_RXFE);
        //return UART2_DR_R & 0xFF;
		break;
        case UART3:
        //while(UART3_FR_R & UART_FR_RXFE);
        //return UART3_DR_R & 0xFF;
		break;
        case UART4:
        //while(UART4_FR_R & UART_FR_RXFE);
        //return UART4_DR_R & 0xFF;
		break;
        case UART5:
        //while(UART5_FR_R & UART_FR_RXFE);
        //return UART5_DR_R & 0xFF;
		break;
        case UART6:
        //while(UART6_FR_R & UART_FR_RXFE);
        //return UART6_DR_R & 0xFF;
		break;
        case UART7:
        //while(UART7_FR_R & UART_FR_RXFE);
        //return UART7_DR_R & 0xFF;
		break;
        default: /*Invalid UART Number*/ break;
    }
		return 0;
}

//////////////////////////////////////////////
//	MOHAMAD SAAD M. HASSAN MULKI 2101894	//
//////////////////////////////////////////////
void UART_ReadStr(u8 copy_u8UARTNum, u8 *copy_pu8GPSData){
	u8 currentChar = UART_u8ReadChar(copy_u8UARTNum);
    while (currentChar != ','){
			*copy_pu8GPSData = currentChar;
			copy_pu8GPSData++;
			currentChar = UART_u8ReadChar(copy_u8UARTNum);
    }
}

///////////////////////////////////////////////
//    Mohamed Magdi Mohamed Ahmed 2100519    //
///////////////////////////////////////////////
//Distance Calculation 
//void APP_voidGetDistance(f32 copy_f32startLatitude, f32 copy_f32startLongitude,f32 copy_f32endLatitude, f32 copy_f32endLongitude, f32 *copy_pf32distance)
//{
//    // convert all coordinates from Degrees into Radians
//    f32 Local_f32startLat = truncate(&copy_f32startLatitude)* M_PI/180;
//    f32 Local_f32startLong = truncate(&copy_f32startLongitude)* M_PI/180;
//    f32 Local_f32endLat = truncate(&copy_f32endLatitude)* M_PI/180;
//    f32 Local_f32endLong = truncate(&copy_f32endLongitude)* M_PI/180;

//    // calculate latitude difference and longitude difference
//    f32 Local_f32latDifference = Local_f32endLat - Local_f32startLat;
//    f32 Local_f32longDifference = Local_f32endLong - Local_f32startLong;

//    //use Haversine formula
//    f32 Local_f32a = sin(Local_f32latDifference / 2) * sin(Local_f32latDifference / 2) + cos(Local_f32startLat) * cos(Local_f32endLat)
//    * sin(Local_f32longDifference / 2) * sin(Local_f32longDifference / 2);
//    f32 Local_f32c = 2 * atan2(sqrt(Local_f32a), sqrt(1 - Local_f32a));

//    //Multipy by Earth's Radius to get the distance
//    *copy_pf32distance = Local_f32c * Earth_Radius;
//}
