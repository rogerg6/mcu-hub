#include "gpio.h"
#include "gpio_stm32f429.h"

void gpio_clk_enable(uint16_t pin) {
  switch (PORTNAME_OF(pin)) {
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
  switch (PORTNAME_OF(pin)) {
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

  gpio_clk_enable(info->pin);
  gpio_set_mode(info, info->mode);
  gpio_set_pull(info, info->pull);
  gpio_set_speed(info, info->speed);
}

void gpio_set_mode(gpio_info_t *info, uint16_t mode) {
  GPIO_TypeDef *port = GPIOx_OF(info->pin);
  uint16_t pin_num = PINx_OF(info->pin);

  // clear bits, equal to set input mode
  port->MODER &= ~(0x3 << (pin_num << 1));

  if (mode & GPIO_PIN_MODE_OUTPUT) {
    port->MODER |= (0x1 << (pin_num << 1));
  }
  else if (mode & GPIO_PIN_MODE_AF) {
    port->MODER |= (0x2 << (pin_num << 1));
  }
  else if (mode & GPIO_PIN_MODE_ANALOG) {
    port->MODER |= (0x3 << (pin_num << 1));
  }

  // PP or OD
  if (mode & GPIO_PIN_MODE_PP)
    port->OTYPER &= ~(0x1 << pin_num);
  else if (mode & GPIO_PIN_MODE_OD)
    port->OTYPER |= 0x1 << pin_num;
}

void gpio_set_pull(gpio_info_t *info, uint8_t pull) {
  GPIO_TypeDef *port = GPIOx_OF(info->pin);
  uint16_t pin_num = PINx_OF(info->pin);

  // clear bits, equal to set pin to float mode
  port->PUPDR &= ~(3 << (pin_num << 1));

  if (pull & GPIO_PIN_PULLUP) {
    port->PUPDR |= (0x1 << (pin_num << 1));
  }
  else if (pull & GPIO_PIN_PULLDOWN) {
    port->PUPDR |= (0x2 << (pin_num << 1));
  }
}

void gpio_set_speed(gpio_info_t *info, uint8_t speed) {
  GPIO_TypeDef *port = GPIOx_OF(info->pin);
  uint16_t pin_num = PINx_OF(info->pin);

  // low speed 2MHz
  port->OSPEEDR &= ~(3 << (pin_num << 1));

  if (speed == GPIO_PIN_SPEED_MEDIUM) {
    // 25MHz
    port->OSPEEDR |= (0x1 << (pin_num << 1));
  }
  else if (speed == GPIO_PIN_SPEED_HIGH) {
    // 50MHz
    port->OSPEEDR |= (0x2 << (pin_num << 1));
  }
  else if (speed == GPIO_PIN_SPEED_VERY_HIGH) {
    // 30 pF 时为 100 MHz（高速）（15 pF 时为 80 MHz 输出（最大速度））
    port->OSPEEDR |= (0x3 << (pin_num << 1));
  }
}

bool gpio_get(gpio_info_t *info) {
  GPIO_TypeDef *port = GPIOx_OF(info->pin);
  uint16_t pin_num = PINx_OF(info->pin);

  return (port->IDR & pin_num) ? true : false;
}


void gpio_set(gpio_info_t *info, bool val) {
  GPIO_TypeDef *port = GPIOx_OF(info->pin);
  uint16_t pin_num = PINx_OF(info->pin);

  if(val == true)
    port->BSRR = (uint32_t)pin_num;
  else
    port->BSRR = (uint32_t)pin_num << 16U;
}

void gpio_toggle(gpio_info_t *info) {
  GPIO_TypeDef *port = GPIOx_OF(info->pin);
  uint16_t pin_num = PINx_OF(info->pin);

  port->ODR ^= (1 << pin_num);
}