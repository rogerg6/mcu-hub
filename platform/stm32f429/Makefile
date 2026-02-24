

obj-y += mcu.c
obj-y += stm32f4xx_it.c
obj-y += stm32f4xx_hal_msp.c
obj-y += sysmem.c
obj-y += syscalls.c
obj-y += system_stm32f4xx.c

# STM32 HAL drivers (always enabled for STM32F429)
obj-y += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
obj-y += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
obj-y += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
obj-y += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
obj-y += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
obj-y += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
obj-y += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c

obj-$(CONFIG_DRIVER_GPIO) += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c

obj-$(CONFIG_DRIVER_UART) += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c

obj-$(CONFIG_DRIVER_SDRAM) += STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.c
obj-$(CONFIG_DRIVER_SDRAM) += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.c

obj-$(CONFIG_DRIVER_LCD) += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc.c
# obj-$(CONFIG_PLATFORM_STM32F429) += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
# obj-$(CONFIG_PLATFORM_STM32F429) += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
# obj-$(CONFIG_PLATFORM_STM32F429) += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
# obj-$(CONFIG_PLATFORM_STM32F429) += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
# obj-$(CONFIG_PLATFORM_STM32F429) += STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c