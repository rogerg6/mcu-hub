#include "modules.h"
#include "platform.h"
#include "led.h"
#include "device.h"


void run_app(void) {
  led_dev_t *led = (led_dev_t *)get_device_by_name("led1");
  if (!led)
    Error_Handler();

  led_on(led);

  while (1) {
    led_toggle(led);
    HAL_Delay(1000);
  }
}

int main(void)
{
  mcu_core_init();
  modules_init();
  run_app();
}// test
