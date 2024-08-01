#include "gsm_sim.h"

static uint32_t old_ms_received;
static uint32_t have_new_data = 0;

#define data_received_size 512

char data_received[data_received_size];
uint32_t data_len;

/*Ngat USART1*/
void USART1_IRQHandler(void){
    //uart_send_string(UART_PORT, "VAO NGAT");
    if(USART_GetITStatus(SIM_USART_PORT, USART_IT_RXNE) != RESET){
        //uart_send_string(UART_PORT, "VAO NGAT");
        char data = USART_ReceiveData(SIM_USART_PORT);

        // if(data_len < data_received_size - 1){
        //     data_received[data_len++] = data;
        // }

		data_received[data_len] = data;
		data_len++;

        old_ms_received = sys_get_tick_ms();
        have_new_data = 1;
        //uart_send_string(UART_PORT, data_received);
		//uart_send_byte(UART_PORT, data);

        //USART_ClearITPendingBit(SIM_USART_PORT, USART_IT_RXNE);
    }
}


void init_gsm_sim(void){

    // Lien ket PA9 PA10 voi TX, RX cua UART1
	GPIO_PinAFConfig(SIM_USART_GPIO, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(SIM_USART_GPIO, GPIO_PinSource10, GPIO_AF_USART1);

	/*GPIO config*/
	GPIO_InitTypeDef gpio_sim;
	gpio_sim.GPIO_Mode = GPIO_Mode_AF;
	gpio_sim.GPIO_Pin = SIM_USART_Tx_Pin | SIM_USART_Rx_Pin;
	gpio_sim.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SIM_USART_GPIO, &gpio_sim);

	/*uart config*/
	USART_InitTypeDef usart1;
	usart1.USART_BaudRate = 115200;
	usart1.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart1.USART_WordLength = USART_WordLength_8b;
	usart1.USART_StopBits = USART_StopBits_1;
    usart1.USART_Parity = USART_Parity_No;
	usart1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(SIM_USART_PORT, &usart1);

	USART_ITConfig(SIM_USART_PORT, USART_IT_RXNE, ENABLE);
	USART_Cmd(SIM_USART_PORT, ENABLE);

	/*nvic config*/
	NVIC_InitTypeDef nvic;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvic.NVIC_IRQChannel = USART1_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	memset(data_received, 0, sizeof(data_received));
	data_len = 0;
}

void init_gsm_power_pin(void){
    /* status */
    GPIO_InitTypeDef gpio5;
    //GPIO_StructInit(&gpio5);
    gpio5.GPIO_Pin = SIM_STATUS_Pin;
    gpio5.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(SIM_STATUS_GPIO, &gpio5);

    /* pwkey */
    GPIO_InitTypeDef gpio6;
    //GPIO_StructInit(&gpio6);
    gpio6.GPIO_Pin = SIM_PWKEY_Pin;
    gpio6.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(SIM_PWKEY_GPIO, &gpio6);
}

uint8_t gsm_get_status(void){
	return GPIO_ReadInputDataBit(SIM_STATUS_GPIO, SIM_STATUS_Pin);
}

void gsm_pull_down_pwr(void){
	GPIO_SetBits(SIM_PWKEY_GPIO, SIM_PWKEY_Pin);
}

void gsm_pull_up_pwr(void){
	GPIO_ResetBits(SIM_PWKEY_GPIO, SIM_PWKEY_Pin);
}


void gsm_sim_send_string(const char *str){
    while (*str){
        while (USART_GetFlagStatus(SIM_USART_PORT, USART_FLAG_TXE) == RESET);
        USART_SendData(SIM_USART_PORT, *str++);
		//uart_send_byte(UART_PORT, *str++);
    }

}

uint32_t gsm_sim_have_new_data(void){
	return have_new_data;
}

uint32_t gsm_sim_get_old_ms_received(void){
	return old_ms_received;
}

uint32_t gsm_sim_get_new_data(char *out_buff){
	if(have_new_data) {
		memcpy(out_buff, data_received, data_len);
		have_new_data = 0;
		return data_len;
	}

	return 0;
}

void gsm_sim_clear_buffer(void){
    memset(data_received, 0, sizeof(data_received));
	data_len = 0;
}
