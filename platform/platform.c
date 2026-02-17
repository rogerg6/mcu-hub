#include "platform.h"
#include "mcu.h"
#include "autoconf.h"

void mcu_core_init(void) 
{
#ifdef CONFIG_PLATFORM_STM32F429
    stm32f429_init();
#endif
}