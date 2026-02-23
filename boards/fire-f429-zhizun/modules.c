/**
 * Use platform=stm32f429
 */
#include "gpio.h"
#include "def.h"
#include "led.h"
#include "uart.h"
#include "modules.h"

// led
led_dev_t led1 = {
    .dev = {
        .name = "led1",
        .next = NULL,
    },
    .gpio = {
        .pin = GPIO_PH(10),
        .mode = GPIO_PIN_MODE_OUTPUT | GPIO_PIN_MODE_OD,
        .pull = GPIO_PIN_PULL_FLOAT,
        .speed = GPIO_PIN_SPEED_LOW,

    },
    .active_high = false,
};

// uart1 for console
uart_dev_t uart1 = {
    .dev = {
        .name = "uart1",
        .next = NULL,
    },
    .tx_pin = GPIO_PA(9),
    .rx_pin = GPIO_PA(10),
    .baudrate = 115200,
    .data_bits = 8,
    .parity = PARITY_NONE,
    .stop_bits = 1,
};
extern UART_HandleTypeDef huart1;

/**
 * printf重定向到UART1
 */
int _write(int file, char *ptr, int len)
{
    if (HAL_OK == HAL_UART_Transmit(&huart1, (const uint8_t *)ptr, len, HAL_MAX_DELAY))
        return len;        
    return -1;
}

void modules_init(void) {
    uart_register(&uart1);
    led_register(&led1);
    sdram_init();
}