#ifndef __GPIO_H
#define __GPIO_H


#include "def.h"
#include "autoconf.h"

#ifdef CONFIG_PLATFORM_STM32F429
#include "gpio_stm32f429.h"
#endif

/* public define ------------------------------------------------------------ */
enum gpio_mode
{
    GPIO_PIN_MODE_INPUT = 0,
    GPIO_PIN_MODE_INPUT_PULLUP,
    GPIO_PIN_MODE_INPUT_PULLDOWN,
    GPIO_PIN_MODE_OUTPUT_PP,
    GPIO_PIN_MODE_OUTPUT_OD,

    GPIO_PIN_MODE_MAX
};


void gpio_init(uint16_t pin);
void gpio_set_mode(uint16_t pin, uint8_t mode);
bool gpio_get(uint16_t pin);
void gpio_set(uint16_t pin, bool status);
void gpio_toggle(uint16_t pin);



#endif
