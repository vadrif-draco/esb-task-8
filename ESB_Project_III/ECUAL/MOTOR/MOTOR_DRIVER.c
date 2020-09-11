//#include "MOTOR_DRIVER.h"
//
//float* steps;
//int8_t current_speed = -1;
//uint8_t num_of_steps = 0;
//uint8_t portNumber = 0;
//uint8_t pinNumber = 0;
//
//void MOTOR_init(EN_EXT_INTERRUPT_t e, EN_INTERRUPT_TRIGGER_t t, EN_SENSITIVITY_t sens, EN_PINS output_pin, float s[], uint8_t size)
//{
//steps = (float*)realloc(steps, size);
//steps = s;
//num_of_steps = size / sizeof(float);
//
//while (output_pin > 7)
//{
//portNumber++;
//output_pin -= 8;
//}
//
//pinNumber = output_pin;
//
//config[portNumber][pinNumber] = output;
//DIO_init(config);
//MOTOR_set_state(LOW);
//
//SOFTPWM_init(e, t, sens, &MOTOR_next_duration, &MOTOR_set_state);
//}
//
//void MOTOR_set_state(EN_pinState_t state)
//{
//DIO_write(portNumber, pinNumber, state);
//}
//
//uint8_t MOTOR_next_duration(void)
//{
//if (current_speed + 1 < num_of_steps)
//{
//current_speed++;
//return (uint8_t) (255.0f * steps[current_speed]);
//}
//else
//{
//current_speed = -1;
//return 0;
//}
//}
//
