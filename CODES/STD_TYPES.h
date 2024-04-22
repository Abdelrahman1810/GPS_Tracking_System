#ifndef __STD_TYPES_H__
#define __STD_TYPES_H__


#define NULL					((void *)0)
#define STD_TYPES_OK			1
#define STD_TYPES_NOK			0
#define DIO_u8_INPUT			0
#define DIO_u8_OUTPUT			1

typedef unsigned char 			u8_t;
typedef unsigned short 			u16_t;
typedef unsigned int 			u32_t;
typedef unsigned long			u64_t;

typedef signed char 			s8;
typedef signed short 			s16;
typedef signed int 				s32;
typedef signed long 			s64;

typedef float					f32;
typedef double					f64;
typedef long double 			f96;


#endif /*the end of STD_TYPES_H */