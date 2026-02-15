#ifndef __LED_H
#define __LED_H

#include "def.h"

typedef struct {
    char name[20];
    uint16_t pin;
    bool active_high;      // 高电平有效
} led_dev_t;


led_dev_t* led_init(const char *name, uint16_t pin, bool active_high);
void led_on(led_dev_t *led);
void led_off(led_dev_t *led);
void led_toggle(led_dev_t *led);



#endif

