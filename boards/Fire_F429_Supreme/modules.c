/**
 * @brief 该文件描述板级硬件信息，类似设备树。调用设备接口注册设备到系统中
 * Use platform=stm32f429
 */
#include "gpio.h"
#include "def.h"
#include "led.h"
#include "uart.h"
#include "lcd.h"
#include "modules.h"

// led
led_dev_t led1 = {
    .dev = {
        .name = "led1",
        .next = NULL,
    },
    .pin = { GPIOH, {GPIO_PIN_10, GPIO_MODE_OUTPUT_OD, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW} },
    .active_high = false,
};

// uart1 for console
uart_dev_t uart1 = {
    .dev = {
        .name = "uart1",
        .next = NULL,
    },
    .tx_pin = {GPIOA, {GPIO_PIN_9, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF7_USART1} },
    .rx_pin = {GPIOA, {GPIO_PIN_10, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF7_USART1} },
    .baudrate = 115200,
    .data_bits = 8,
    .parity = PARITY_NONE,
    .stop_bits = 1,
};
extern UART_HandleTypeDef huart1;

/* printf重定向到UART1 */
int _write(int file, char *ptr, int len)
{
    if (HAL_OK == HAL_UART_Transmit(&huart1, (const uint8_t *)ptr, len, HAL_MAX_DELAY))
        return len;        
    return -1;
}

// 5.0寸lcd tft 
/* LTDC GPIO Configuration */
static gpio_info_t lcd_pins[] = {
    {GPIOD, {GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW}}, // LCD_BL
    {GPIOD, {GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW}}, // LCD_DISP

    {GPIOG, {GPIO_PIN_7, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_CLK
    {GPIOI, {GPIO_PIN_9, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_VSYNC
    {GPIOI, {GPIO_PIN_10, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},    // LTDC_HSYNC
    {GPIOF, {GPIO_PIN_10, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},    // LTDC_DE

    {GPIOH, {GPIO_PIN_2, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_R0
    {GPIOH, {GPIO_PIN_3, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_R1
    {GPIOH, {GPIO_PIN_8, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_R2
    {GPIOB, {GPIO_PIN_0, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF9_LTDC}},      // LTDC_R3
    {GPIOA, {GPIO_PIN_11, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},    // LTDC_R4
    {GPIOA, {GPIO_PIN_12, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},    // LTDC_R5
    {GPIOB, {GPIO_PIN_1, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF9_LTDC}},      // LTDC_R6
    {GPIOG, {GPIO_PIN_6, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_R7

    {GPIOE, {GPIO_PIN_5, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_G0
    {GPIOE, {GPIO_PIN_6, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_G1
    {GPIOH, {GPIO_PIN_13, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},    // LTDC_G2
    {GPIOG, {GPIO_PIN_10, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF9_LTDC}},     // LTDC_G3
    {GPIOH, {GPIO_PIN_15, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},    // LTDC_G4
    {GPIOI, {GPIO_PIN_0, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_G5
    {GPIOC, {GPIO_PIN_7, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_G6
    {GPIOI, {GPIO_PIN_2, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_G7

    {GPIOE, {GPIO_PIN_4, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_B0
    {GPIOG, {GPIO_PIN_12, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},    // LTDC_B1
    {GPIOD, {GPIO_PIN_6, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_B2
    {GPIOG, {GPIO_PIN_11, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},    // LTDC_B3
    {GPIOI, {GPIO_PIN_4, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_B4
    {GPIOA, {GPIO_PIN_3, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_B5
    {GPIOB, {GPIO_PIN_8, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_B6
    {GPIOB, {GPIO_PIN_9, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF14_LTDC}},     // LTDC_B7
};

lcd_info_t lcd = {
    .width = 800,
    .height = 480,
    .hsw = 1,
    .hbp = 46,
    .hfp = 22,
    .vsw = 1,
    .vbp = 23,
    .vfp = 22,
    .pfmt = PIXEL_FORMAT_RGB888,
    .alpha = 255,
    .fb_base_addr = SDRAM_BASE_ADDR,

    .pins = lcd_pins,
    .n_pins = sizeof(lcd_pins) / sizeof(gpio_info_t),
    .bl_pin = &lcd_pins[0],
    .disp_pin = &lcd_pins[1],
};

void modules_init(void) {
    uart_register(&uart1);
    led_register(&led1);
    sdram_init();
    lcd_init(&lcd);
}


