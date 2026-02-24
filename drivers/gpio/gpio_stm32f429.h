#ifndef __GPIO_STM32F429_H
#define __GPIO_STM32F429_H

#include "stm32f4xx_hal.h"

// #define GPIO_PA(x)  (x)
// #define GPIO_PB(x)  (16*1 + x)
// #define GPIO_PC(x)  (16*2 + x)
// #define GPIO_PD(x)  (16*3 + x)
// #define GPIO_PE(x)  (16*4 + x)
// #define GPIO_PF(x)  (16*5 + x)
// #define GPIO_PG(x)  (16*6 + x)
// #define GPIO_PH(x)  (16*7 + x)
// #define GPIO_PI(x)  (16*8 + x)

// eg. GPIOB -> 'B'
#define PORTNAME_OF(port) ((((uint32_t)(port) - AHB1PERIPH_BASE) >> 10) + 'A')

// // eg. 17 -> GPIOB
// #define GPIOx_OF(pin) ((GPIO_TypeDef*)(AHB1PERIPH_BASE + ((pin >> 4) << 10)))

// #define PINx_OF(pin) (pin & 0xF)
// #define PIN_OF(pin) (1 << (pin & 0xF))

typedef struct {
    GPIO_TypeDef *port;
    GPIO_InitTypeDef config;
} gpio_info_t;



#endif
