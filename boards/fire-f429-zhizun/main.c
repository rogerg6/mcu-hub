#include "main.h"
#include "platform.h"
#include "led.h"
#include "gpio.h"


void run_app(void) {
  led_dev_t *led = led_init("led1", GPIO_PH(10), false);
  led_on(led);

  while (1) {
    led_toggle(led);
    HAL_Delay(1000);
  }
}

int main(void)
{
  mcu_core_init();
  run_app();
}