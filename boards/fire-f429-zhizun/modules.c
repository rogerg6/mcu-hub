#include "gpio.h"
#include "def.h"
#include "led.h"

// led
led_dev_t led1 = {
    .dev = {
        .name = "led1",
        .next = NULL,
    },
    .pin = GPIO_PH(10),
    .pin_mode = GPIO_PIN_MODE_OUTPUT_OD,
    .active_high = false,
};

void modules_init(void) {
    led_register(&led1);
}