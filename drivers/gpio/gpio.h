#ifndef __GPIO_H
#define __GPIO_H


#include "def.h"
#include "device.h"
#include "autoconf.h"

#ifdef CONFIG_PLATFORM_STM32F429
#include "gpio_stm32f429.h"
#endif

/* public define ------------------------------------------------------------ */


void gpio_clk_enable(gpio_info_t *info);
void gpio_clk_disable(gpio_info_t *info);
void gpio_init(gpio_info_t *info);
void gpio_deinit(gpio_info_t *info);
bool gpio_get(gpio_info_t *info);
void gpio_set(gpio_info_t *info, bool status);
void gpio_toggle(gpio_info_t *info);



#endif
