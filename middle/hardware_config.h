#ifndef __HARDWARE_CONFIG_H__
#define __HARDWARE_CONFIG_H__

#include "stm32f4xx.h"

/* Define Led pin*/
#define LED_PIN			                    GPIO_Pin_9
#define LED_PORT			                GPIOB

/* Define Button pin */
#define BTN_PIN					            GPIO_Pin_0
#define BTN_PORT					        GPIOA

/* Define PC UART pin */
#define UART_TX_GPIO_PIN				    GPIO_Pin_2
#define UART_RX_GPIO_PIN				    GPIO_Pin_3
#define UART_GPIO				            GPIOA
#define UART_PORT					        USART2

/* Define GSM Uart Pin */
#define		SIM_USART_Tx_Pin				GPIO_Pin_9
#define		SIM_USART_Rx_Pin				GPIO_Pin_10
#define		SIM_USART_GPIO					GPIOA
#define		SIM_USART_PORT					USART1

#define 	SIM_STATUS_Pin					GPIO_Pin_12
#define		SIM_STATUS_GPIO					GPIOA

#define 	SIM_PWKEY_Pin					GPIO_Pin_8
#define		SIM_PWKEY_GPIO					GPIOA


#endif /*__HARDWARE_CONFIG_H__*/
