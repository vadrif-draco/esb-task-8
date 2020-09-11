#include "../../HWL/REGS.h"
#include "../../MCAL/DIO/DIO_driver.h"
#include "../../Application/typedefs.h"

void DIO_init(EN_DIO_config_t configurations)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
            if (configurations[j][i] == output)
                *(DDRA - 3 * j) |= configurations[j][i] << i;
            else
                *(DDRA - 3 * j) &= ~( !configurations[j][i] << i);
        }
    }
}

void DIO_write(vuint8_t port, uint8_t bit, EN_pinState_t ps)
{
    // check if pin is input or output, if the latter, write to it.
    // registers are offset by the value defined in "port" variable.
    if ( *( DDRA - 3 * port ) & (1 << bit))
    {
        if (ps)
            *( PORTA - 3 * port ) |= (1 << bit);
        else
            *( PORTA - 3 * port ) &= ~(1 << bit);
    }
}

EN_pinState_t DIO_read(vuint8_t port, uint8_t bit)
{
    // like in DIO_write, registers are offset by the value defined in "port" variable.
    return *( PINA - 3 * port ) & (1 << bit);
}

void DIO_toggle(vuint8_t port, uint8_t bit)
{
    DIO_write(port, bit, DIO_read(port, bit) ? LOW : HIGH);
}