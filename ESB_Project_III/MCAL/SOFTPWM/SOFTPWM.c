#include "SOFTPWM.h"

EN_CLOCKSOURCE_t clock_source;
int8_t current_speed = -1;
uint8_t num_of_steps = 0;
vuint8_t port_number = 0;
uint8_t pin_number = 0;
float* steps;

void SOFTPWM_init(float s[],
                  uint8_t size,
                  EN_PINS output_pin,
                  EN_EXT_INTERRUPT_t e,
                  EN_INTERRUPT_TRIGGER_t t,
                  EN_SENSITIVITY_t sensitivity)
{
    steps = (float*)realloc(steps, size);
    steps = s;
    num_of_steps = size / sizeof(float);
    
    while (output_pin > 7)
    {
        port_number++;
        output_pin -= 8;
    } pin_number = output_pin;
    
    config[port_number][pin_number] = output; // Initialize target pin as output
    DIO_init(config);
    
    clock_source = sensitivity;
    
    // Here we set the 3rd and 6th bits of TCCR0 to set the counter/timer mode
    *TCCR0 &= ~((1 << 3) | (1 << 6)); // 1011 1011 --> Clearing both bits = NORMAL mode
    
    switch (e)
    {
        case INT0:
        {
            *MCUCR |= t;
            break;
        }
        
        case INT1:
        {
            *MCUCR = t << 2;
            break;
        }
        
        case INT2:
        {
            // no idea
            break;
        }
        
        default:
            break;
    }
    
    *TIMSK |= (1 << 0); // Setting TOIE0 so overflow causes an interrupt
    *TIMSK |= (1 << 1); // Setting OCIE0 so output compare match causes an interrupt
    *SREG |= 1 << 7;
    *GICR |= 1 << e;
}

//	For PWM modes:
//	Duty Cycle %ge = OCR/max "which is 255 for 8-bit timers", hence:
//
//	OCR = 255 × Duty Cycle %ge

uint8_t next_duty_cycle(void)
{
    if (current_speed + 1 < num_of_steps)
    {
        current_speed++;
        return (uint8_t) (255.0f * steps[current_speed]);
    }
    else
    {
        current_speed = -1;
        return 0;
    }
}

// ISR for external interrupt 0
void __vector_1(void)
{

    *OCR0 = next_duty_cycle(); // Get the next duration to be done in PWM
    set_HIGH();
    *TCCR0 |= clock_source; // Start the timer with preset clock source
}

// ISR for T0 Compare Match
void __vector_10(void)
{
    set_LOW();
}

// ISR for T0 Overflow
void __vector_11(void)
{
    if (*OCR0) // If non-zero... *** (Read below)
        set_HIGH();
}

inline void set_HIGH(void)
{
    *( PORTA - 3 * port_number ) |= (1 << pin_number);
}

inline void set_LOW(void)
{
    *( PORTA - 3 * port_number ) &= ~(1 << pin_number);
}

/* ***	While debugging on Proteus, interrupts seemed to interrupt each other...
		Additionally, upon setting OCR0 to 0, its interrupt is never triggered...
		In that case, only the overflow will get triggered (with target pin set HIGH)...
		This led to unwanted behavior, and the solution was to add that if condition.
		*/