#include "../../Application/typedefs.h"
#include "LED_Driver.h"
#include "../../MCAL/DIO/DIO_driver.h"

void LED_init(EN_PINS pinNumber, EN_pinState_t defaultState)
{
    vuint8_t portNumber = 0;
    
    while (pinNumber > 7)
    {
        portNumber++;
        pinNumber -= 8;
    }
    
    config[portNumber][pinNumber] = output;
    DIO_init(config);
    DIO_write(portNumber, pinNumber, defaultState);
}
void LED_setState(EN_PINS pinNumber, EN_pinState_t state)
{
    vuint8_t portNumber = 0;
    
    while (pinNumber > 7)
    {
        portNumber++;
        pinNumber -= 8;
    }
    
    DIO_write(portNumber, pinNumber, state);
}

void LED_toggle(EN_PINS pinNumber)
{
    vuint8_t portNumber = 0;
    
    while (pinNumber > 7)
    {
        portNumber++;
        pinNumber -= 8;
    }
    
    DIO_toggle(portNumber, pinNumber);
}

EN_pinState_t LED_read(EN_PINS pinNumber)
{
    vuint8_t portNumber = 0;
    
    while (pinNumber > 7)
    {
        portNumber++;
        pinNumber -= 8;
    }
    
    return DIO_read(portNumber, pinNumber);
}