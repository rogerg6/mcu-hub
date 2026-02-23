#include "modules.h"
#include "platform.h"
#include "led.h"
#include "uart.h"
#include "device.h"
#include <stdio.h>


void run_app(void) {
  uart_dev_t *uart1 = (uart_dev_t *)get_device_by_name("uart1");
  if (!uart1) Error_Handler();

  led_dev_t *led = (led_dev_t *)get_device_by_name("led1");
  if (!led) Error_Handler();

  sdram_test();

  while (1) {
    led_toggle(led);
    uart_writeb(uart1, 'X');
    HAL_Delay(1000);
  }
}

int main(void)
{
  mcu_core_init();
  modules_init();

  printf("MCU_HUB: board=Fire stm32f429IGT6\n");

  run_app();
}
