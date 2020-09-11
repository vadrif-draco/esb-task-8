#include "BTN_Driver.h"
#include "../../MCAL/DIO/DIO_driver.h"
#include "../../Application/typedefs.h"

void BTN_init(EN_PINS pinNumber)
{
    vuint8_t portNumber = 0;
    
    while (pinNumber > 7)
    {
        portNumber++;
        pinNumber -= 8;
    }
    
    config[portNumber][pinNumber] = input;
    DIO_init(config);
}
EN_pinState_t BTN_read(EN_PINS pinNumber)
{
    vuint8_t portNumber = 0;
    
    while (pinNumber > 7)
    {
        portNumber++;
        pinNumber -= 8;
    }
    
    return DIO_read(portNumber, pinNumber);
}