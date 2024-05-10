#include "BIT_MATH.h"
#include "interface.h"
#include "private.h"
#include "STD_TYPES.h"
#include "tm4c123gh6pm.h"
#include "string.h"
#include "stdint.h"
#define LEN 10
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

/*
	void isCLKWork(u32 SYSCTL_PRGPIO) {
		if (!GET_BIT(SYSCTL_PRGPIO_R, SYSCTL_PRGPIO))
		{
			SET_BIT(SYSCTL_SCGCGPIO_R, SYSCTL_PRGPIO); // Enable port clock
			while (!GET_BIT(SYSCTL_PRGPIO_R, SYSCTL_PRGPIO)); // Wait till enabled
		}
		return;
	}
*/

//void isCLKWork(u32 SYSCTL_PRGPIO) {
//	if (!GET_BIT(SYSCTL_PRGPIO_R, SYSCTL_PRGPIO))
//	{
//		SET_BIT(SYSCTL_SCGCGPIO_R, SYSCTL_PRGPIO); // Enable port clock
//		while (!GET_BIT(SYSCTL_PRGPIO_R, SYSCTL_PRGPIO)); // Wait till enabled
//	}
//	return;
//}

//////////////////////////////////
//	Engy Khaled Sayed 2100610	//
//////////////////////////////////
void RGBLED_init(void){
	SYSCTL_RCGCGPIO_R |= PF_mask; //clock of portf
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
///////////////////////////////
//Engy Khaled Sayed//
/////////////////////////////
//init of TIMER
void SysTick_Init(u64 delay){
	NVIC_ST_CTRL_R = 0x00;//disable systick during setup
	NVIC_ST_RELOAD_R = delay-1;//number of counts
	NVIC_ST_CURRENT_R = 0x00; //to clear
	NVIC_ST_CTRL_R  = 0x05 ; //enable systick
	while ((NVIC_ST_CTRL_R  & 0x00010000)==0){
		//wait for flag
	}
}
void SysTick_Wait(u64  delay){
	u64 i;
	for(i=0 ; i<delay ; i++){
		SysTick_Init(80000000); //1sec
	}
}

//////////////////////////////////////////
//	Sarah Hamed Mahmoud Alsayed 2101518	//
//////////////////////////////////////////
void PushButtonInit(){
	SET_BIT(SYSCTL_RCGCGPIO_R,PF_mask); //configure clk for portf
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

void Is_Sw_Pressed(u8 SW2 )
{   
   SW2 = Sw_Input();
 if (SW2/* && distance >= 100*/)
      LEDs_Output (RED) ;
}


/* UART functions */
// Baud Rate = 9600 bits/sec 
// 16 MHz System Clock  , ClkDivision=16
///////////////////////////////////////////

///////////////////////////////////////////////
//		Eman Sherif Sayed Ragheb 2100721     // 
///////////////////////////////////////////////
void UART0_Init(void) {
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
	GPIO_PORTA_AMSEL_R &= ~0x03; // disable analog func for PA0 ,PA1
}

///////////////////////////////////////////////
//		Eman Sherif Sayed Ragheb 2100721     // 
///////////////////////////////////////////////
void UART1_Init(void) {
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
//		Eman Sherif Sayed Ragheb 2100721     // 
///////////////////////////////////////////////
int UART0_Available(void){
   return ((UART0_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}
char UART0_read(){
   while(UART0_Available() != 1);
   return UART0_DR_R & 0xFF;
}
void UART0_write(char c){
   while((UART0_FR_R & UART_FR_TXFF) != 0);
   UART0_DR_R = c;
}

void GET_Command(char *str, int maxLEN){
   char c;
   int i;
   for(i = 0; i < maxLEN; i++){
    c = UART0_read();
    if( c== '\n' || c == '\r') break;
    else str[i] = c;
    UART0_write(c);
}
}  
void printStr(char *str){
   while(*str){
    UART0_write(*str);
    str++;
}
}
void UART0_SendByte(int Data)
{
		while(UART0_FR_R & UART_FR_TXFF);
		
		UART0_DR_R = Data;
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
			while(UART2_FR_R & UART_FR_RXFE);
			return UART2_DR_R & 0xFF;
        case UART3:
			while(UART3_FR_R & UART_FR_RXFE);
			return UART3_DR_R & 0xFF;
        case UART4:
			while(UART4_FR_R & UART_FR_RXFE);
			return UART4_DR_R & 0xFF;
        case UART5:
			while(UART5_FR_R & UART_FR_RXFE);
			return UART5_DR_R & 0xFF;
        case UART6:
			while(UART6_FR_R & UART_FR_RXFE);
			return UART6_DR_R & 0xFF;
        case UART7:
			while(UART7_FR_R & UART_FR_RXFE);
			return UART7_DR_R & 0xFF;
        default: /*Invalid UART Number*/ break;
    }
}

//////////////////////////////////////////////
//	MOHAMAD SAAD M. HASSAN MULKI 2101894	//
//////////////////////////////////////////////
void UART_ReadStr(u8 copy_u8UARTNum, u8 *copy_pu8GPSData){
	u8 currentChar = UART_u8ReadChar(copy_u8UARTNum);
    while (currentChar != ','){
        *copy_pu8GPSData = currentChar;
        copy_pu8GPSData++;
		u8 currentChar = UART_u8ReadChar(copy_u8UARTNum);
    }
}

/////////////////////////
// /* DIO functions */ //
///////////////////////// 

//////////////////////////////////////////////
//	MOHAMAD SAAD M. HASSAN MULKI 2101894	//
//////////////////////////////////////////////
u8 u8SetPinDirection (u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection) {
	if (copy_u8PinId >= u8_PIN_0 && copy_u8PinId <= u8_PIN_7) //Check if pin number is valid
	{
		switch (copy_u8PortId)
		{
		case u8PORT_A:
			SET_BIT(SYSCTL_SCGCGPIO_R, SYSCTL_RCGCGPIO_R0); // Enable port clock
			while (!GET_BIT(SYSCTL_PRGPIO_R, SYSCTL_PRGPIO_R0)); // Wait till enabled
			switch (copy_u8PinDirection)
			{
			case u8_INPUT:
				CLR_BIT(GPIO_PORTA_DIR_R, copy_u8PinId);
				break;

			case u8_OUTPUT:
				SET_BIT(GPIO_PORTA_DIR_R, copy_u8PinId);
				break;
			default:
				return STD_TYPES_NOK; // Invalid direction
			}
			break;

		case u8PORT_B:
			break;
		case u8PORT_C:
			break;
		case u8PORT_D:
			break;
		case u8PORT_E:
			break;
		case u8PORT_F:
			break;
		default:
			return STD_TYPES_NOK; // Invalid port
		}
		return STD_TYPES_OK; // No errors
	}
	else
		return STD_TYPES_NOK; // Invalid pin number
}
//////////////////////////////////////
//	Sarah Hamed Mahmoud Alsayed 2101518	//
//////////////////////////////////////
void sendData(char *longitude ,char *lat){

	while(*longitude) {
		UART1_Write(*longitude);
		longitude++;
	}

	while(*lat) {
		UART1_Write(*lat);
		lat++;
	}
} 


//////////////////////////////////////
//	Abdelrahman Mohamed Ali 2100347	//
//////////////////////////////////////
u8 u8SetPinValue (u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue) {
	//Check if pin number and port name is valid
	if (  (copy_u8PinId >= u8_PIN_0 && copy_u8PinId <= u8_PIN_7) 
		&&(copy_u8PortId <= u8PORT_F && copy_u8PortId>=u8PORT_A))
	{
		switch (copy_u8PortId)
		{
		case u8PORT_A:
			SET_BIT(SYSCTL_SCGCGPIO_R, SYSCTL_RCGCGPIO_R0); // Enable port clock
			while (!GET_BIT(SYSCTL_PRGPIO_R, SYSCTL_PRGPIO_R0)); // Wait till enabled
			
			switch (copy_u8PinValue)
			{
			case u8_HIGH:
				SET_BIT(GPIO_PORTA_DATA_R, copy_u8PinId);
				break;
			case u8_LOW:
				CLR_BIT(GPIO_PORTA_DATA_R, copy_u8PinId);
				break;
			default:
				return STD_TYPES_NOK; // Invalid direction
			}
			break;
		case u8PORT_F:
			SET_BIT(SYSCTL_SCGCGPIO_R, SYSCTL_RCGCGPIO_R5); // Enable port clock
			while (!GET_BIT(SYSCTL_PRGPIO_R, SYSCTL_RCGCGPIO_R5)); // Wait till enabled
			
			switch (copy_u8PinValue)
			{
			case u8_HIGH:
				SET_BIT(GPIO_PORTF_DATA_R, copy_u8PinId);
				break;
			case u8_LOW:
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

///////////////////////////////////////////////
//    Mohamed Magdi Mohamed Ahmed 2100519    //
///////////////////////////////////////////////
u8 u8GetPinValue (u8 copy_u8PortId, u8 copy_u8PinId, u8 *copy_pu8ReturnedPinValue) {
   if((copy_pu8ReturnedPinValue != NULL)
   		&&(copy_u8PortId <= u8PORT_F && copy_u8PortId>=u8PORT_A)
		&&(copy_u8PinId  >= u8_PIN_0 && copy_u8PinId<=u8_PIN_7)) {
		switch(copy_u8PortId)
		{
			case u8PORT_A:
				SET_BIT(SYSCTL_SCGCGPIO_R, SYSCTL_RCGCGPIO_R0); // Enable port clock
				while (!GET_BIT(SYSCTL_PRGPIO_R, SYSCTL_PRGPIO_R0)); // Wait till enabled
				
				*copy_pu8ReturnedPinValue = GET_BIT(GPIO_PORTA_DATA_R,copy_u8PinId);
				
				switch(*copy_pu8ReturnedPinValue) {
					case u8_HIGH:
						*copy_pu8ReturnedPinValue = u8_HIGH;
						break;
					case u8_LOW :
						*copy_pu8ReturnedPinValue = u8_LOW;
						break;
					default:
						return STD_TYPES_NOK; // Invalid Value
				}
			break;

		case u8PORT_B:
			break;
		case u8PORT_C:
			break;
		case u8PORT_D:
			break;
		case u8PORT_E:
			break;
		case u8PORT_F:
			break;
		default:
			return STD_TYPES_NOK; // Invalid port
		}
	}
	else
	return STD_TYPES_NOK;
}

///////////////////////////////////////////////
//		Eman Sherif Sayed Ragheb 2100721     // 
///////////////////////////////////////////////
u8 u8SetPortDirection(u8 copy_u8PortId, u8 copy_u8PortDirection ){
	if(copy_u8PortId >= u8PORT_A &&copy_u8PortId <= u8PORT_F)       //check if PortId is valid
	{
		SET_BIT(SYSCTL_RCGCGPIO_R,copy_u8PortId); 						// To enable a clock and active PORT A
		while(!GET_BIT(SYSCTL_PRGPIO_R,copy_u8PortId)); 			// Wait till the Clock be stable
		switch(copy_u8PortId)
		{
			case u8PORT_A:
				GPIO_PORTA_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTA_CR_R    = GPIO_ENABLE_7_BIT;						// Allow changes to PA7-0 
				GPIO_PORTA_AFSEL_R = 0x00;												// Disable analog functions
				GPIO_PORTA_PCTL_R  = GPIO_PCTL_VALUE; 						// GPIO_PCTL_VALUE-->To make all pins in PORT A work as DIO 
				GPIO_PORTA_DEN_R   = 0xFF;												// to enable pin PA0-PA7 as digital 
			break;
			case u8PORT_B:
				GPIO_PORTB_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTB_CR_R    = GPIO_ENABLE_7_BIT;						// Allow changes to PA7-0 
				GPIO_PORTB_AFSEL_R = 0x00;												// Disable the alternative functions
				GPIO_PORTB_PCTL_R  = GPIO_PCTL_VALUE; 						// GPIO_PCTL_VALUE-->To make all the pins in PORT B work as DIO 
				GPIO_PORTB_DEN_R   = 0xFF;												// to enable the pin PB0-PB7 as digital 
			break;
			case u8PORT_C:
				GPIO_PORTC_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTC_CR_R    = GPIO_ENABLE_7_BIT;						// Allow changes to PA7-0 
				GPIO_PORTC_AFSEL_R = 0x00;												// Disable the alternative functions
				GPIO_PORTC_PCTL_R  = GPIO_PCTL_VALUE; 						// GPIO_PCTL_VALUE-->To make all the pins in PORT C work as DIO  
				GPIO_PORTC_DEN_R   = 0xFF;												// to enable the pin PB0-PB7 as digital 
			break;
			case u8PORT_D:
				GPIO_PORTD_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTD_CR_R    = GPIO_ENABLE_7_BIT;						// Allow changes to PA7-0 
				GPIO_PORTD_AFSEL_R = 0x00;												// Disable the alternative functions
				GPIO_PORTD_PCTL_R  = GPIO_PCTL_VALUE; 						// GPIO_PCTL_VALUE-->To make all the pins in PORT D work as DIO
				GPIO_PORTD_DEN_R   = 0xFF;												// to enable the pin PD0-PD7 as digital 
			break;
			case u8PORT_E:
				GPIO_PORTE_LOCK_R  = GPIO_LOCK_KEY; 							// Unlocks the GPIOCR register so we can allow the commit
				GPIO_PORTE_CR_R    = GPIO_ENABLE_7_BIT;						// Allow changes to PA7-0 
				GPIO_PORTE_AFSEL_R = 0x00;												// Disable the alternative functions
				GPIO_PORTE_PCTL_R  = GPIO_PCTL_VALUE; 						// GPIO_PCTL_VALUE-->To make all the pins in PORT E work as DIO 
				GPIO_PORTE_DEN_R   = 0xFF;												// to enable the pin PE0-PE7 as digital 
			break;
			case u8PORT_F:
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
	
   if ( copy_u8PortDirection==u8_OUTPUT||copy_u8PortDirection==u8_INPUT) // check if PortDirection is valid
   {
		switch(copy_u8PortId)
		{
			case u8PORT_A:
				switch(copy_u8PortDirection){
					case u8_INPUT: GPIO_PORTA_DIR_R=0x00; break;
					case u8_OUTPUT: GPIO_PORTA_DIR_R=0xFF; break;
					default: return STD_TYPES_NOK;
				}
				break;
			case u8PORT_B:
				switch(copy_u8PortDirection){
			    	case u8_INPUT: GPIO_PORTA_DIR_R=0x00; break;
					case u8_OUTPUT: GPIO_PORTA_DIR_R=0xFF; break;
					default: return STD_TYPES_NOK;
				}
				break;
			case u8PORT_C:
				switch(copy_u8PortDirection){
					case u8_INPUT: GPIO_PORTA_DIR_R=0x00; break;
					case u8_OUTPUT: GPIO_PORTA_DIR_R=0xFF; break;
					default: return STD_TYPES_NOK;
				}
				break;
			case u8PORT_D:
				switch(copy_u8PortDirection){
					case u8_INPUT: GPIO_PORTA_DIR_R=0x00; break;
					case u8_OUTPUT: GPIO_PORTA_DIR_R=0xFF; break;
					default: return STD_TYPES_NOK;
				}
				break;
			case u8PORT_E:
				switch(copy_u8PortDirection){
					case u8_INPUT: GPIO_PORTA_DIR_R=0x00; break;
					case u8_OUTPUT: GPIO_PORTA_DIR_R=0xFF; break;
					default: return STD_TYPES_NOK;
				}
				break;
			case u8PORT_F:
				switch(copy_u8PortDirection){
					case u8_INPUT: GPIO_PORTA_DIR_R=0x00; break;
					case u8_OUTPUT: GPIO_PORTA_DIR_R=0xFF; break;
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

//////////////////////////////////////////
//	Sarah Hamed Mahmoud Alsayed 2101518	//
//////////////////////////////////////////
u8 u8SetPortValue		(u8 copy_u8PortId, u8 copy_u8PortValue){
switch(copy_u8PortId)
	{

		case u8PORT_A:
		GPIO_PORTA_DATA_R=copy_u8PortValue;
		break;
		case u8PORT_B:
		GPIO_PORTB_DATA_R=copy_u8PortValue;
		break;
		case u8PORT_C:
		GPIO_PORTC_DATA_R=copy_u8PortValue;
		break;
		case u8PORT_D:
		GPIO_PORTD_DATA_R=copy_u8PortValue;
		break;
		case u8PORT_E:
		GPIO_PORTE_DATA_R=copy_u8PortValue;
		break;
		case u8PORT_F:
		GPIO_PORTF_DATA_R=copy_u8PortValue;
		break;
		default: //invalid port
		return STD_TYPES_NOK;
		break;
		return STD_TYPES_NOK;
	}
}

//////////////////////////////////
//	Engy Khaled Sayed 2100610	//
//////////////////////////////////
u8 u8GetPortValue		(u8 copy_u8PortId, u8 *copy_u8ReturnedPortValue)
{
     if(copy_u8ReturnedPortValue != NULL && ((copy_u8PortId >=u8PORT_A)&&(copy_u8PortId <=u8PORT_F)))
    {
        switch (copy_u8PortId)
        {
            case u8PORT_A:*copy_u8ReturnedPortValue = GPIO_PORTA_DATA_R;
            break;
             case u8PORT_B:*copy_u8ReturnedPortValue = GPIO_PORTB_DATA_R;
            break;
             case u8PORT_C:*copy_u8ReturnedPortValue = GPIO_PORTC_DATA_R;
            break;
             case u8PORT_D:*copy_u8ReturnedPortValue = GPIO_PORTD_DATA_R;
            break;
             case u8PORT_E:*copy_u8ReturnedPortValue = GPIO_PORTE_DATA_R;
            break;
             case u8PORT_F:*copy_u8ReturnedPortValue = GPIO_PORTF_DATA_R;
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

///////////////////////////////////////////////
//    Mohamed Magdi Mohamed Ahmed 2100519    //
///////////////////////////////////////////////
//Distance Calculation 
void APP_voidGetDistance(f32 copy_f32startLatitude, f32 copy_f32startLongitude,f32 copy_f32endLatitude, f32 copy_f32endLongitude, f32 *copy_pf32distance)
{
    // convert all coordinates from Degrees into Radians
    f32 Local_f32startLat = truncate(&copy_f32startLatitude)* M_PI/180;
    f32 Local_f32startLong = truncate(&copy_f32startLongitude)* M_PI/180;
    f32 Local_f32endLat = truncate(&copy_f32endLatitude)* M_PI/180;
    f32 Local_f32endLong = truncate(&copy_f32endLongitude)* M_PI/180;

    // calculate latitude difference and longitude difference
    f32 Local_f32latDifference = Local_f32endLat - Local_f32startLat;
    f32 Local_f32longDifference = Local_f32endLong - Local_f32startLong;

    //use Haversine formula
    f32 Local_f32a = sin(Local_f32latDifference / 2) * sin(Local_f32latDifference / 2) + cos(Local_f32startLat) * cos(Local_f32endLat)
    * sin(Local_f32longDifference / 2) * sin(Local_f32longDifference / 2);
    f32 Local_f32c = 2 * atan2(sqrt(Local_f32a), sqrt(1 - Local_f32a));

    //Multipy by Earth's Radius to get the distance
    *copy_pf32distance = Local_f32c * Earth_Radius;
}
