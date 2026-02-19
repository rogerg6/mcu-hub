#ifndef __UART_H
#define __UART_H

#include "platform.h"
#include "def.h"
#include "device.h"

enum PARIT_TYPE {
    PARITY_NONE=0,
    PARITY_EVEN,
    PARITY_ODD,
};

typedef struct {
    dev_t dev;

    void *handle;       // ¾ä±ú
    uint16_t tx_pin;
    uint16_t rx_pin;

    uint32_t baudrate;
    uint8_t data_bits;
    bool parity;
    uint8_t stop_bits;
} uart_dev_t;


int uart_register(uart_dev_t *dev);
int uart_init(uart_dev_t *dev);
void uart_deinit(uart_dev_t *dev);
int uart_readb(uart_dev_t *dev, uint8_t *val);
int uart_writeb(uart_dev_t *dev, uint8_t val);



#endif

