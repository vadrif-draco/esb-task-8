#ifndef _REGS_H_
#define _REGS_H_

#include "../Application/typedefs.h"


// DIO Registers Addresses _______
#define PORTA	(vuint8_t*)(0x3B)
#define DDRA	(vuint8_t*)(0x3A)
#define PINA	(vuint8_t*)(0x39)

#define PORTB	(vuint8_t*)(0x38)
#define DDRB	(vuint8_t*)(0x37)
#define PINB	(vuint8_t*)(0x36)

#define PORTC	(vuint8_t*)(0x35)
#define DDRC	(vuint8_t*)(0x34)
#define PINC	(vuint8_t*)(0x33)

#define PORTD	(vuint8_t*)(0x32)
#define DDRD	(vuint8_t*)(0x31)
#define PIND	(vuint8_t*)(0x30)

// TIMER Registers Addresses ____

#define OCR0	(vuint8_t*)(0x5C)
#define OCR2	(vuint8_t*)(0x43)

#define TIFR	(vuint8_t*)(0x58)

#define TCCR0	(vuint8_t*)(0x53)
#define TCCR2	(vuint8_t*)(0x45)

#define TIMSK	(vuint8_t*)(0x59)

#define TCNT0	(vuint8_t*)(0x52)
#define TCNT2	(vuint8_t*)(0x44)

// Interrupts Handling Regs _____

#define SREG	(vuint8_t*)(0x5F) // Status register
#define GICR	(vuint8_t*)(0x5B) // General Interrupt Control Register
#define MCUCR	(vuint8_t*)(0x55) // MCU Control register

#endif