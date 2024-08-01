/*
 * init.c
 *
 *  Created on: Jul 25, 2024
 *      Author: MinhAnh
 */

#include "init.h"

void enable_clock(void){
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}

void init(void){
    enable_clock();
    init_led();
    init_systick();
    init_uart();
    init_gsm_sim();
    init_gsm_power_pin();
    init_button();
}


