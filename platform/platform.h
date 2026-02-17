#ifndef __PLATFORM_H
#define __PLATFORM_H

#include "autoconf.h"
#include "mcu.h"


#ifdef CONFIG_PLATFORM_STM32F429
#include "stm32f4xx_hal.h"
#endif


void mcu_core_init(void);


#endif

