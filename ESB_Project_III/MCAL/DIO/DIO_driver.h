#ifndef DIO_DRIVER_H_
#define DIO_DRIVER_H_

#include "../../Application/typedefs.h"

typedef enum {input, output} EN_DIO_config_t[4][8];
EN_DIO_config_t config;

void DIO_init(EN_DIO_config_t configurations);

void DIO_write(vuint8_t port, uint8_t bit, EN_pinState_t ps);
EN_pinState_t DIO_read(vuint8_t port, uint8_t bit);
void DIO_toggle(vuint8_t port, uint8_t bit);

#endif /* DIO_CONTROL_H_ */