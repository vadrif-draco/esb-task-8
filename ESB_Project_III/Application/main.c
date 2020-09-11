#include "../ECUAL/LED/LED_Driver.h"
#include "../ECUAL/BTN/BTN_Driver.h"
#include "../MCAL/SOFTPWM/SOFTPWM.h"

int main(void)
{
    BTN_init(D2);
    
    float speeds[] = {0.2, 0.4, 0.6, 0.8, 1};
    SOFTPWM_init(speeds, sizeof(speeds), D7, INT0, RISING, SENSITIVITY5);
    
    // The configuration above is enough to give the following functionality:
    //	- Button initialized on D2(INT0)
    //	- PWM output setup on D7 listening to INT0 (which is on D2)'s rising edge,
    //	cycling through speeds array every time the button is pressed via its ISR,
    //	listening with a sensitivity level that corresponds to a certain prescaler.
    //	- SENSITIVITY[1 --> 5] correspond to clock sources [no_prescaler --> /1024]
    //
    // The higher the inertia of the target, the higher the sensitivity should be.
    
    LED_init(C0, HIGH); // A DC motor is used here instead of an LED to test max speed on Proteus for comparison
    
    while (1);
    
    return 0;
}