#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

// Signed typedefs ________________________________________
typedef signed char			int8_t;
typedef signed short		int16_t;		//	predefined?
typedef signed long			int32_t;
typedef signed long long	int64_t;


// Unsigned typedefs ______________________________________
typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;		//	predefined?
typedef unsigned long		uint32_t;
typedef unsigned long long	uint64_t;


// Signed typedefs limits _________________________________
#define INT8_MIN			-0x7f - 1
#define INT8_MAX			0x7f
#define INT16_MIN			-0x7fff - 1
#define INT16_MAX			0x7fff
#define INT32_MIN			-0x7fffffff - 1
#define INT32_MAX			0x7fffffff
#define INT64_MIN			-0x7fffffffffffffff - 1
#define INT64_MAX			0x7fffffffffffffff


// Unsigned typedefs limits _______________________________
#define UINT8_MAX			0xff
#define UINT16_MAX			0xffff
#define UINT32_MAX			0xffffffff
#define UINT64_MAX			0xffffffffffffffff


// ATmega32 typedefs ______________________________________
typedef volatile uint8_t vuint8_t;

typedef enum {LOW, HIGH} EN_pinState_t;

typedef enum {TIMER0, TIMER1, TIMER2} EN_TIMER_t;

typedef enum {NORMAL, CTC, PCPWM, FPWM} EN_TIMERMODE_t;

typedef enum {noclk, clk, clk_8, clk_64, clk_256, clk_1024,
              clk_ext_falling, clk_ext_rising
             } EN_CLOCKSOURCE_t;

typedef enum {SENSITIVITY1 = 1, SENSITIVITY2, SENSITIVITY3, SENSITIVITY4, SENSITIVITY5} EN_SENSITIVITY_t;

typedef enum {	A0, A1, A2, A3, A4, A5, A6, A7,
                B0, B1, B2, B3, B4, B5, B6, B7,
                C0, C1, C2, C3, C4, C5, C6, C7,
                D0, D1, D2, D3, D4, D5, D6, D7,
                T0 = B0,
                T1 = B1,
                OC0 = B3,
                OC2 = D7
             }	EN_PINS;

typedef enum {INT0 = 6, INT1 = 7, INT2 = 5} EN_EXT_INTERRUPT_t;

typedef enum {LEVEL_LOW, ANY_EDGE, FALLING, RISING} EN_INTERRUPT_TRIGGER_t;

#endif