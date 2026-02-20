#ifndef __LED_H
#define __LED_H

#include "def.h"
#include "gpio.h"
#include "device.h"

typedef struct {
    dev_t dev;
    gpio_info_t gpio;
    bool active_high;      // 高电平有效
} led_dev_t;


int led_register(led_dev_t *led);
void led_on(led_dev_t *led);
void led_off(led_dev_t *led);
void led_toggle(led_dev_t *led);



#endif

