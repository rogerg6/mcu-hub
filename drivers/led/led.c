#include "led.h"
#include "gpio.h"
#include <string.h>
#include <assert.h>

led_dev_t led1;

led_dev_t* led_init(const char *name, uint16_t pin, bool active_high)
{
    assert(name != NULL);

    strcpy(led1.name, name);
    led1.pin = pin;
    led1.active_high = active_high;

    gpio_init(pin);
    gpio_set_mode(pin, GPIO_PIN_MODE_OUTPUT_OD);

    return &led1;
}

void led_on(led_dev_t *led)
{
    gpio_set(led->pin, led->active_high ? 1 : 0);
}

void led_off(led_dev_t *led)
{
    gpio_set(led->pin, led->active_high ? 0 : 1);
}

void led_toggle(led_dev_t *led)
{
    gpio_toggle(led->pin);
}