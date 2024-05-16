#ifndef __interface_h__
#define __interface_h__

//GPIO_prototypes
void GPIOF_Handler(void);
void PORTF_Initial(void);
void RGB_SetOutput(unsigned char data);
void RGB_ClearOutput(unsigned char data);
void RGB_ToggleOutput(void);

//GPS_prototypes
bool GPS_voidReceiveSentence( char *Local_u8GPS_Sentence );
f32 truncate(f32 *copy_f32FloatValue);
void APP_voidGetDistance(f32 copy_f32startLatitude, f32 copy_f32startLongitude,f32 copy_f32endLatitude, f32 copy_f32endLongitude, f32 *copy_pf32distance);
void GPS_voidExtractCoordinates(u8 *copy_pu8Sentence, u8 *copy_u8Longitude,u8 *copy_u8Latitude );

//UART_prototypes
void uart2_init();
void uart2_send(uint8_t character);
void uart2_send_string(char * string);
char uart2_receive();
void uart2_receive_string(char * string, uint32_t len);
void uart5_init();
void uart5_send(uint8_t character);
void uart5_send_string(char * string);
char uart5_receive();
void uart5_receive_string(char * string, uint32_t len);

//SYSTICK_prototypes
void systick_init(void);
void wait_1ms(void);
void delay(int t);
bool chk_start();
bool get_cordinates();
bool chk_FIX();
#endif 
