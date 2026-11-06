#ifndef PROJECTDEFINES_H_
#define PROJECTDEFINES_H_

#define F_CPU 16000000UL
#define Upper_Lower_Bit_Value 0x20

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>

typedef void (*Function_Pointer_With_One_CharPointer_Parameter)(char *);

#if defined(_AVR_ATMEGA328PB_H_INCLUDED) || defined(_AVR_IOM2560_H_)
#define USR0_Vect_Num USART0_RX_vect
#define GreenLedBit   PORTB1
#define YellowLedBit  PORTB2
#define RedLedBit     PORTB3
#elif defined(_AVR_IOM168_H_) || defined(_AVR_IOM328P_H_)
#define USR0_Vect_Num USART_RX_vect
#endif

#endif