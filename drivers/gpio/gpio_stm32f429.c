#include "gpio.h"
#include "gpio_stm32f429.h"

void gpio_clk_enable(uint16_t pin) {
  switch (PIN_2_PORT(pin)) {
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

void gpio_clk_disable(uint16_t pin) {
  switch (PIN_2_PORT(pin)) {
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

void gpio_init(uint16_t pin)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_TypeDef *port = pin_2_gpiox(pin);
  uint16_t pin_num = pin_2_portpin(pin);

  gpio_clk_enable(pin);

  HAL_GPIO_WritePin(port, pin_num, GPIO_PIN_SET);

  GPIO_InitStruct.Pin = pin_num;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void gpio_set_mode(uint16_t pin, uint8_t mode) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_TypeDef *port = pin_2_gpiox(pin);
  uint16_t pin_num = pin_2_portpin(pin);

  GPIO_InitStruct.Pin = pin_num;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  if (mode == GPIO_PIN_MODE_INPUT) {
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
  }
  else if (mode == GPIO_PIN_MODE_INPUT_PULLUP) {
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
  }
  else if (mode == GPIO_PIN_MODE_INPUT_PULLDOWN) {
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  }
  else if (mode == GPIO_PIN_MODE_OUTPUT_PP) {
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
  }
  else if (mode == GPIO_PIN_MODE_OUTPUT_OD) {
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
  }

  HAL_GPIO_Init(port, &GPIO_InitStruct);
}

bool gpio_get(uint16_t pin) {
  GPIO_TypeDef *port = pin_2_gpiox(pin);
  uint16_t pin_num = pin_2_portpin(pin);

  return HAL_GPIO_ReadPin(port, pin_num);
}


void gpio_set(uint16_t pin, bool val) {
  GPIO_TypeDef *port = pin_2_gpiox(pin);
  uint16_t pin_num = pin_2_portpin(pin);

  HAL_GPIO_WritePin(port, pin_num, val);
}

void gpio_toggle(uint16_t pin) {
  GPIO_TypeDef *port = pin_2_gpiox(pin);
  uint16_t pin_num = pin_2_portpin(pin);

  port->ODR ^= pin_num;
}