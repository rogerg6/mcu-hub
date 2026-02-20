#include "led.h"
#include "gpio.h"
#include "device.h"

/**
 * ×¢²á²¢³õÊ¼»¯led
 */
int led_register(led_dev_t *led)
{
    assert_param(led != NULL);

    gpio_init(&led->gpio);

    return device_register((dev_t*)led);
}

void led_on(led_dev_t *led)
{
    gpio_set(&led->gpio, led->active_high ? 1 : 0);
}

void led_off(led_dev_t *led)
{
    gpio_set(&led->gpio, led->active_high ? 0 : 1);
}

void led_toggle(led_dev_t *led)
{
    gpio_toggle(&led->gpio);
}