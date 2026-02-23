#include "uart.h"
#include "gpio.h"
#include "platform.h"
#include <string.h>

UART_HandleTypeDef huart1;

int uart_register(uart_dev_t *dev){
    int err;
    assert_param(dev != NULL);

    err = uart_init(dev);
    if (err)
        return err;
    return device_register((dev_t*)dev);
}

int uart_init(uart_dev_t *dev){
    assert_param(dev != NULL);

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    UART_HandleTypeDef *huart;
    GPIO_TypeDef *tx_port = GPIOx_OF(dev->tx_pin);
    GPIO_TypeDef *rx_port = GPIOx_OF(dev->rx_pin);
    uint16_t tx_pin_num = PIN_OF(dev->tx_pin);
    uint16_t rx_pin_num = PIN_OF(dev->rx_pin);

    __HAL_RCC_USART1_CLK_ENABLE();
    gpio_clk_enable(dev->tx_pin);
    gpio_clk_enable(dev->rx_pin);

    GPIO_InitStruct.Pin = tx_pin_num;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(tx_port, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = rx_pin_num;
    HAL_GPIO_Init(rx_port, &GPIO_InitStruct);

    if (!strcmp("uart1", dev->dev.name)) {
        huart = &huart1;
        huart->Instance = USART1;
    }
    huart->Init.BaudRate = dev->baudrate;

    if (dev->data_bits == 8)
        huart->Init.WordLength = UART_WORDLENGTH_8B;
    else if (dev->data_bits == 9)
        huart->Init.WordLength = UART_WORDLENGTH_9B;

    if (dev->stop_bits == 1)
        huart->Init.StopBits = UART_STOPBITS_1;
    else if (dev->stop_bits == 2)
        huart->Init.StopBits = UART_STOPBITS_2;

    if (dev->parity == PARITY_NONE)
        huart->Init.Parity = UART_PARITY_NONE;
    else if (dev->parity == PARITY_EVEN)
        huart->Init.Parity = UART_PARITY_EVEN;
    else if (dev->parity == PARITY_ODD)
        huart->Init.Parity = UART_PARITY_ODD;

    huart->Init.Mode = UART_MODE_TX_RX;
    huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart->Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(huart) != HAL_OK)
        goto err;

    dev->handle = (void*)huart;
    return OK;

err:
    uart_deinit(dev);
    return ERR;

}

void uart_deinit(uart_dev_t *dev){
    assert_param(dev != NULL);

    GPIO_TypeDef *tx_port = GPIOx_OF(dev->tx_pin);
    GPIO_TypeDef *rx_port = GPIOx_OF(dev->rx_pin);
    uint16_t tx_pin_num = PINx_OF(dev->tx_pin);
    uint16_t rx_pin_num = PINx_OF(dev->rx_pin);

    if (!strcmp("uart1", dev->dev.name)) {
        __HAL_RCC_USART1_CLK_DISABLE();
    }

    HAL_GPIO_DeInit(tx_port, tx_pin_num);
    HAL_GPIO_DeInit(rx_port, rx_pin_num);
}

int uart_readb(uart_dev_t *dev, uint8_t *val){
    assert_param(dev != NULL);
    assert_param(val != NULL);

    UART_HandleTypeDef *huart = (UART_HandleTypeDef *)(dev->handle);
    if (HAL_OK != HAL_UART_Receive(huart, val, 1, HAL_MAX_DELAY))
        return ERR_IO;
    else
        return OK;
}

int uart_writeb(uart_dev_t *dev, uint8_t val){
    assert_param(dev != NULL);

    UART_HandleTypeDef *huart = (UART_HandleTypeDef *)(dev->handle);
    if (HAL_OK != HAL_UART_Transmit(huart, &val, 1, HAL_MAX_DELAY))
        return ERR_IO;
    else
        return OK;
}
