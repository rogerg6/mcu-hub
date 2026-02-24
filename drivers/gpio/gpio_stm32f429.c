#include "gpio_stm32f429.h"
#include "def.h"

void gpio_clk_enable(gpio_info_t *info) {
  switch (PORTNAME_OF(info->port)) {
    case 'A': __HAL_RCC_GPIOA_CLK_ENABLE(); break;
    case 'B': __HAL_RCC_GPIOB_CLK_ENABLE(); break;
    case 'C': __HAL_RCC_GPIOC_CLK_ENABLE(); break;
    case 'D': __HAL_RCC_GPIOD_CLK_ENABLE(); break;
    case 'E': __HAL_RCC_GPIOE_CLK_ENABLE(); break;
    case 'F': __HAL_RCC_GPIOF_CLK_ENABLE(); break;
    case 'G': __HAL_RCC_GPIOG_CLK_ENABLE(); break;
    case 'H': __HAL_RCC_GPIOH_CLK_ENABLE(); break;
    case 'I': __HAL_RCC_GPIOI_CLK_ENABLE(); break;
  }
}

void gpio_clk_disable(gpio_info_t *info) {
  switch (PORTNAME_OF(info->port)) {
    case 'A': __HAL_RCC_GPIOA_CLK_DISABLE(); break;
    case 'B': __HAL_RCC_GPIOB_CLK_DISABLE(); break;
    case 'C': __HAL_RCC_GPIOC_CLK_DISABLE(); break;
    case 'D': __HAL_RCC_GPIOD_CLK_DISABLE(); break;
    case 'E': __HAL_RCC_GPIOE_CLK_DISABLE(); break;
    case 'F': __HAL_RCC_GPIOF_CLK_DISABLE(); break;
    case 'G': __HAL_RCC_GPIOG_CLK_DISABLE(); break;
    case 'H': __HAL_RCC_GPIOH_CLK_DISABLE(); break;
    case 'I': __HAL_RCC_GPIOI_CLK_DISABLE(); break;
  }
}

void gpio_init(gpio_info_t *info)
{
  assert_param(info != NULL);
  gpio_clk_enable(info);
  HAL_GPIO_Init(info->port, &info->config);
}

void gpio_deinit(gpio_info_t *info)
{
  assert_param(info != NULL);
  gpio_clk_disable(info);
  HAL_GPIO_DeInit(info->port, info->config.Pin);
}

bool gpio_get(gpio_info_t *info) {
  return HAL_GPIO_ReadPin(info->port, info->config.Pin) ? true : false;
}


void gpio_set(gpio_info_t *info, bool val) {
  HAL_GPIO_WritePin(info->port, info->config.Pin, (GPIO_PinState)val);
}

void gpio_toggle(gpio_info_t *info) {
  info->port->ODR ^= info->config.Pin;
}