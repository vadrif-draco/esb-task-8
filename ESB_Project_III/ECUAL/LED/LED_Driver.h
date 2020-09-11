#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include "../../Application/typedefs.h"

void LED_init(EN_PINS pinNumber, EN_pinState_t defaultState);
void LED_setState(EN_PINS pinNumber, EN_pinState_t state);
EN_pinState_t LED_read(EN_PINS pinNumber);
void LED_toggle(EN_PINS pinNumber);

#endif /* LED_DRIVER_H_ */