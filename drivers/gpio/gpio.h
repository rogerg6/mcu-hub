#ifndef __GPIO_H
#define __GPIO_H


#include "def.h"
#include "device.h"
#include "autoconf.h"

#ifdef CONFIG_PLATFORM_STM32F429
#include "gpio_stm32f429.h"
#endif

/* public define ------------------------------------------------------------ */
#define GPIO_PIN_MODE_INPUT         0x0001
#define GPIO_PIN_MODE_OUTPUT        0x0002
#define GPIO_PIN_MODE_PP            0x0004
#define GPIO_PIN_MODE_OD            0x0008
#define GPIO_PIN_MODE_AF            0x0010
#define GPIO_PIN_MODE_ANALOG        0x0020

#define GPIO_PIN_PULLUP        0x01
#define GPIO_PIN_PULLDOWN      0x02
#define GPIO_PIN_PULL_FLOAT    0x04

enum {
    GPIO_PIN_SPEED_LOW = 0,
    GPIO_PIN_SPEED_MEDIUM,
    GPIO_PIN_SPEED_HIGH,
    GPIO_PIN_SPEED_VERY_HIGH,
};

typedef struct {
    uint16_t pin;
    uint16_t mode;
    uint8_t pull;
    uint8_t speed;

    // void *data;     // 平台相关数据. eg. GPIO port
} gpio_info_t;


void gpio_clk_enable(uint16_t pin);
void gpio_clk_disable(uint16_t pin);
void gpio_init(gpio_info_t *info);
void gpio_set_mode(gpio_info_t *info, uint16_t mode);
void gpio_set_pull(gpio_info_t *info, uint8_t pull);
void gpio_set_speed(gpio_info_t *info, uint8_t pull);
bool gpio_get(gpio_info_t *info);
void gpio_set(gpio_info_t *info, bool status);
void gpio_toggle(gpio_info_t *info);



#endif
