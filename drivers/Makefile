# Makefile for drivers directory

# GPIO driver
ifeq ($(CONFIG_DRIVER_GPIO),y)
obj-$(CONFIG_PLATFORM_STM32F429) += gpio/gpio_stm32f429.c
endif

# LED driver
obj-$(CONFIG_DRIVER_LED) += led/led.c