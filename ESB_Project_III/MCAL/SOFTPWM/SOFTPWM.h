#ifndef SOFTPWM_H_
#define SOFTPWM_H_

#include <stdlib.h> // For dynamic memory allocation functions
#include "../../Application/typedefs.h"
#include "../DIO/DIO_driver.h"
#include "../../HWL/REGS.h"

/**
\brief
 Initialize function should take the following attributes:

 	An array of floats determining the different levels of PWM to go through
	The size of the array (just use sizeof on the array entered previously)
 	The output pin to apply the generated PWM waveform onto
	The interrupt pin to listen on (INT0 or INT1 or INT2)
	The interrupt trigger (rising edge, falling, etc...)
	Motor sensitivity (used in choosing clock source)
*/
void SOFTPWM_init(float s[],
                  uint8_t size,
                  EN_PINS output_pin,
                  EN_EXT_INTERRUPT_t e,
                  EN_INTERRUPT_TRIGGER_t t,
                  EN_SENSITIVITY_t sensitivity);

uint8_t next_duty_cycle(void);
void set_HIGH(void);
void set_LOW(void);

void __vector_1(void) __attribute__ ((signal, used)); // ISR for external interrupt 0
/*
void __vector_2(void) __attribute__ ((signal, used)); // ISR for external interrupt 1
void __vector_3(void) __attribute__ ((signal, used)); // ISR for external interrupt 2
void __vector_4(void) __attribute__ ((signal, used)); // Timer/Counter2 Compare Match
void __vector_5(void) __attribute__ ((signal, used)); // Timer/Counter2 Overflow
void __vector_6(void) __attribute__ ((signal, used)); // Timer/Counter1 Capture Event
void __vector_7(void) __attribute__ ((signal, used)); // Timer/Counter1 Compare Match A
void __vector_8(void) __attribute__ ((signal, used)); // Timer/Counter1 Compare Match B
void __vector_9(void) __attribute__ ((signal, used)); // Timer/Counter1 Overflow
*/
void __vector_10(void) __attribute__ ((signal, used)); // Timer/Counter0 Compare Match
void __vector_11(void) __attribute__ ((signal, used)); // Timer/Counter0 Overflow

#endif /* SOFTPWM_H_ */