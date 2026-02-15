#include "platform.h"

static void stm32f429_init(void) {
    HAL_Init();
    SystemClock_Config();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
}


void mcu_core_init(void) {
    stm32f429_init();
}