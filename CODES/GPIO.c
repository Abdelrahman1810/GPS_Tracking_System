#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "STD_TYPES.h"
#include "interface.h"

void GPIOF_Handler(void);
void PORTF_Initial(void);
void RGB_SetOutput(unsigned char data);
void RGB_ClearOutput(unsigned char data);
void RGB_ToggleOutput(void);

///////////////////////////////////////////////
//    Sarah Hamed Mahmoud Alsayed 2101518    //
///////////////////////////////////////////////

void GPIOF_Handler(void)   // PORTF Handler For Interrupt
{ 
    if(GPIO_PORTF_MIS_R&0x10)
    { 
        UART5_CTL_R &= ~UART_CTL_UARTEN;    // Disable the UART 
		GPIO_PORTF_DATA_R |= 0x02;          //Turn red led on
        GPIO_PORTF_ICR_R |=0x10; 
    }       
}

void PORTF_Initial(void)  //Initialize All in PortF For Interrupt
{    
    SYSCTL_RCGCGPIO_R  |= 0x20 ;   //PF Clock config 
    while ( (SYSCTL_PRGPIO_R & 0x20 ) == 0 ) ; 
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY ;  // GPIO_LOCK_KEY = 0x4C4F434B
    GPIO_PORTF_CR_R  |= 0x1F ;  
    GPIO_PORTF_AMSEL_R &= ~0x1F ;
    GPIO_PORTF_AFSEL_R &= ~0x1F ;
    GPIO_PORTF_PCTL_R  &= ~ 0x000FFFFF ; // clear bits in PCTL
    GPIO_PORTF_DIR_R   |= 0x0E ;  // enable output dir for bits 1,2,3
    GPIO_PORTF_DEN_R   |= 0x1F ;  // enable bits as digital
    GPIO_PORTF_DATA_R  &= ~ 0x0E ; // clear bits
    GPIO_PORTF_PUR_R  |=0x11 ;    // pull up resistors for switchs
    GPIO_PORTF_IS_R  &=~0x11 ; //edge not level
    GPIO_PORTF_IBE_R  &=~0x11; //not both edges
    GPIO_PORTF_IEV_R  &=~0x11;  //falling edge
    GPIO_PORTF_IM_R  |=0x11 ;   //enable interrupt
    NVIC_PRI7_R=(NVIC_PRI7_R&0xFF00FFFF)|(1<<22); //setting portf priority  
    NVIC_EN0_R |=(1<<30);  //EN0,bit30
}

//RGB Set
void RGB_SetOutput(unsigned char data){
    GPIO_PORTF_DATA_R |= data;
}

//RGB Clear
void RGB_ClearOutput(unsigned char data){
    GPIO_PORTF_DATA_R &=~ data;
}

//RGB Toggle
void RGB_ToggleOutput(void){
    GPIO_PORTF_DATA_R ^= 1;
}
