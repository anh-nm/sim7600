#include "uart.h"

void init_uart(void){

    //
	GPIO_PinAFConfig(UART_GPIO, GPIO_PinSource2, GPIO_AF_USART2);

	GPIO_InitTypeDef gpio_uart;
	gpio_uart.GPIO_Mode = GPIO_Mode_AF;
	gpio_uart.GPIO_Pin = UART_TX_GPIO_PIN;
	gpio_uart.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(UART_GPIO, &gpio_uart);

	USART_InitTypeDef usart2;
	usart2.USART_BaudRate = 115200;
	usart2.USART_Mode = USART_Mode_Tx;
	usart2.USART_WordLength = USART_WordLength_8b;
	usart2.USART_StopBits = USART_StopBits_1;
	usart2.USART_Parity = USART_Parity_No;
	usart2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(UART_PORT, &usart2);

	USART_Cmd(UART_PORT, ENABLE);
}

void uart_send_string(USART_TypeDef *USARTx, const char *str){
    while (*str){
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
        USART_SendData(USARTx, *str++);
    }
}

void uart_send_byte(USART_TypeDef *USARTx, uint8_t data){
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    USART_SendData(USARTx, data);
    //while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
}


