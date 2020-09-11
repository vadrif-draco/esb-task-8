#ifndef BTN_DRIVER_H_
#define BTN_DRIVER_H_

#include "../../Application/typedefs.h"

void BTN_init(EN_PINS pinNumber);
EN_pinState_t BTN_read(EN_PINS pinNumber);

#endif /* BTN_DRIVER_H_ */