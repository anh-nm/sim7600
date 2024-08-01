#ifndef __UART_H__
#define __UART_H__

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "misc.h"
#include "hardware_config.h"
#include "string.h"
//#include <stdio.h>

void init_uart(void);
void uart_send_string(USART_TypeDef *USARTx, const char *str);
void uart_send_byte(USART_TypeDef *USARTx, uint8_t data);


#endif /*__UART_H__*/
