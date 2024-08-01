/*
 * button.c
 *
 *  Created on: Jul 25, 2024
 *      Author: MinhAnh
 */

#include "button.h"


void init_button(void){

	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio.GPIO_Pin = BTN_PIN;
	GPIO_Init(BTN_PORT, &gpio);

}

uint8_t get_btn_status(void){
	return GPIO_ReadInputDataBit(BTN_PORT, BTN_PIN);
}

button_state button_loop(void){
	static uint32_t old_click_ms = 0;
	static uint32_t time_to_wait = 0;
	static uint8_t status = NO_CLICK;
	static uint32_t time_long_click = 0;
	static uint8_t time_click = CLICK;
	static uint32_t time_wait_click = 0;

	if(sys_get_tick_ms() - old_click_ms < time_to_wait){
		return 0;
	}

	old_click_ms = sys_get_tick_ms();

	switch (status)
	{
	case NO_CLICK:
		if(get_btn_status() == BTN_ON){
			status = HOLD_BUTTON;
			//old_click_ms = sys_get_tick_ms();
			time_to_wait = 50;
		}
		break;

	case CLICK:
		uart_send_string(UART_PORT, "CLICK\r\n");
		time_click = CLICK;
		status = NO_CLICK;
		
		break;
	
	case DOUBLE_CLICK:
		uart_send_string(UART_PORT, "DOUBLE CLICK\r\n");
		time_click = CLICK;
		status = NO_CLICK;

		break;

	case TRIBLE_CLICK:
		uart_send_string(UART_PORT, "TRIBLE CLICK\r\n");
		time_click = CLICK;
		status = NO_CLICK;

		break;
	
	case LONG_CLICK:
		uart_send_string(UART_PORT, "LONG CLICK\r\n");
		status = NO_CLICK;
		break;

	case HOLD_BUTTON:
		if(get_btn_status() == BTN_ON){
			status = HOLD_BUTTON_LONG;
			time_long_click = sys_get_tick_ms();

		}else{
			//if(sys_get_tick_ms()-)
			status = WAIT_CLICK;
			time_wait_click = sys_get_tick_ms();
		}
		break;

	case HOLD_BUTTON_LONG:
		if(get_btn_status() == BTN_OFF){
			if(sys_get_tick_ms() - time_long_click >= 4000){
				status = LONG_CLICK;
				time_long_click = 0;
			}else{
				status = WAIT_CLICK;
				time_wait_click = sys_get_tick_ms();
				time_long_click = 0;
			}
		}
		break;

	case WAIT_CLICK:
		if(sys_get_tick_ms() - time_wait_click < 500){
			if(get_btn_status() == BTN_ON){
				time_click ++;
				status = HOLD_BUTTON;
			}
		}
		else{
			if(time_click > 3){
				time_click = CLICK; 
				status = NO_CLICK;
				break;
			}
			status = time_click;
		}
		
		break;
	
	default:
		break;
	}

	return status;
}



