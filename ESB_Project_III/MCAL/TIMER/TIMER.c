#include "../../ECUAL/LED/LED_Driver.h"
#include "TIMER.h"
#include <math.h>

void TIMER_init(EN_TIMER_t t, EN_TIMERMODE_t tm)
{
    // Here we set the bits of the relevant TCCRn
    // Since bits 6 and 3 are the ones that control timer mode, then...
    // ...we create a temporary variable to store the specific settings
    vuint8_t temp = 0x00;
    
    switch (tm)
    {
        case NORMAL:
            temp &= ~((1 << 3) | (1 << 6)); // 1011 1011 --> Clearing both bits
            break;
            
        case PCPWM:
            temp |= (1 << 3); // 0000 0100 --> Setting bit 3
            temp &= ~(1 << 6); // 1011 1111 --> Clearing bit 6
            break;
            
        case CTC:
            temp &= ~(1 << 3); // 1111 1011 --> Clearing bit 3
            temp |= (1 << 6); // 0100 0000 --> Setting bit 6
            break;
            
        case FPWM:
            temp |= (1 << 3) | (1 << 6); // 0100 0100 --> Setting both bits
            break;
    }
    
    // Then we set the respective timer
    switch (t)
    {
        case TIMER0:
        {
            *TCCR0 |= temp;
            break;
        }
        
        // I don't know what to do with TIMER1
        case TIMER1:
            break;
            
        case TIMER2:
        {
            *TCCR2 |= temp;
            break;
        }
    }
    
    // Possible modes are: NORMAL, CTC, PCPWM, FPWM, respectively.
    // *** NOTICE: Setting the mode doesn't immediately start the timer!
}

void TIMER_setValue(EN_TIMER_t t, vuint8_t value)
{
    // To set values, we use the TCNTn registers
    switch (t)
    {
        case TIMER0:
        {
            *TCNT0 |= value;
            break;
        }
        
        // I don't know what to do with TIMER1
        case TIMER1:
            break;
            
        case TIMER2:
        {
            *TCNT2 |= value;
            break;
        }
    }
}

void TIMER_setOCR(EN_TIMER_t t, vuint8_t value)
{
    // To set values, we use the TCNTn registers
    switch (t)
    {
        case TIMER0:
        {
            *OCR0 = value;
            break;
        }
        
        // I don't know what to do with TIMER1
        case TIMER1:
            break;
            
        case TIMER2:
        {
            *OCR2 = value;
            break;
        }
    }
}

void TIMER_start(EN_TIMER_t t, EN_CLOCKSOURCE_t cs, vuint8_t startVal)
{
    // First, we set the starting value before the timer starts. This action doesn't start the timer.
    TIMER_setValue(t, startVal);
    
    // To actually start the timer, we have to set its clock source, then it immediately starts counting.
    // To set the clock source, we use the respective TCCRn register to adjust bits 2:0.
    switch (t)
    {
        case TIMER0:
        {
            *TCCR0 |= (vuint8_t) cs;
            break;
        }
        
        // I don't know what to do with TIMER1
        case TIMER1:
            break;
            
        case TIMER2:
        {
            *TCCR2 |= (vuint8_t) cs;
            break;
        }
    }
}

void TIMER_stop(EN_TIMER_t t)
{
    // As mentioned above, the first 3 TCCRn bits control the timer. Here, to stop it, we set them to zero.
    // We also reset TCNTn to zero for extra measure.
    switch (t)
    {
        case TIMER0:
        {
            *TCCR0 &= (0xFF << 3); // 1111 1000
            *TCNT0 = 0;
            break;
        }
        
        // I don't know what to do with TIMER1
        case TIMER1:
            break;
            
        case TIMER2:
        {
            *TCCR2 &= (0xFF << 3); // 1111 1000
            *TCNT2 = 0;
            break;
        }
    }
}

/* The following info is useful for the next functions:

	____________________ TIFR Register Bits ____________________

	7		6		5		4		3		2		1		0
	OCF2	TOV2	ICF1	OCF1A	OCF1B	TOV1	OCF0	TOV0
	____________________________________________________________

	However task 7 is only concerned with normal/overflow mode, so we'll only be concerned with bits 0 and 6.
*/


void TIMER_delay_us(EN_TIMER_t t, uint32_t micros)
{


    /*
        // First we get the mode this timer is setup with
        EN_TIMERMODE_t tm;
    
        switch (t)
        {
            case TIMER0:
            {
                tm |= ( (*TCCR0 & 1 << 3) | (*TCCR0 & 1 << 6) );
                break;
            }
    
            // I don't know what to do with TIMER1
            case TIMER1:
                break;
    
            case TIMER2:
            {
                tm |= ( (*TCCR2 & 1 << 3) | (*TCCR2 & 1 << 6) );
                break;
            }
        }
    
    // In task 7 we only use normal timer
    */
    
    if (micros <= 255)
        TIMER_start(t, clk, 255 - micros);
    else if (micros <= 2047)
        TIMER_start(t, clk_8, 255 - (uint8_t)(micros * (255.0 / 2047.0)));
    else if (micros <= 16383)
        TIMER_start(t, clk_64, 255 - (uint8_t)(micros * (255.0 / 16383.0)));
    else if (micros <= 65535)
        TIMER_start(t, clk_256, 255 - (uint8_t)(micros * (255.0 / 65535.0)));
    else if (micros <= 262143)
        TIMER_start(t, clk_1024, 255 - (uint8_t)(micros * (255.0 / 262143.0)));
    else
        return;
        
    switch (t)
    {
    
        case TIMER0:
        {
            while (!(*TIFR & (1 << 0))); // 0000 0001
            
            *TIFR |= (1 << 0); // 0000 0001 *clears the flag*
            TIMER_stop(t);
            break;
        }
        
        // I don't know what to do with TIMER1
        case TIMER1:
            break;
            
        case TIMER2:
        {
            while (!(*TIFR & (1 << 6))); // 0100 0000
            
            TIMER_stop(t);
            *TIFR &= (1 << 6); // 0100 0000
            break;
        }
    }
    
}

void TIMER_delay_ms(EN_TIMER_t t, uint16_t millis)
{
    if (millis <= 262)
        TIMER_delay_us(t, millis * 1000);
    else
    {
        for (uint8_t i = 0; i < ceil(millis / 262.0); i++)
        {
            // Split into two parts so I can see the iterations happening on A0
            LED_setState(A0, HIGH);
            TIMER_delay_us(t, (millis / ceil(millis / 262.0)) * 500);
            LED_setState(A0, LOW);
            TIMER_delay_us(t, (millis / ceil(millis / 262.0)) * 500);
        }
    }
}