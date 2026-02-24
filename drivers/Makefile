# Makefile for drivers directory

# common
obj-y += common/device.c

# GPIO driver
ifeq ($(CONFIG_DRIVER_GPIO),y)
obj-$(CONFIG_PLATFORM_STM32F429) += gpio/gpio_stm32f429.c
endif

# LED driver
obj-$(CONFIG_DRIVER_LED) += led/led.c

# GPIO driver
ifeq ($(CONFIG_DRIVER_UART),y)
obj-$(CONFIG_PLATFORM_STM32F429) += uart/uart_stm32f429.c
endif

ifeq ($(CONFIG_DRIVER_LCD),y)
obj-$(CONFIG_PLATFORM_STM32F429) += lcd/ltdc_stm32f429.c
obj-y += common/font/fonts.c
endif