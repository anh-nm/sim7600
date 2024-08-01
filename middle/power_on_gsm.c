/*
 * power_on_gsm.c
 *
 *  Created on: Jul 26, 2024
 *      Author: MinhAnh
 */

#include "power_on_gsm.h"

static sq_t queue_data;

void gsm_data_receive(void){
    if(gsm_sim_have_new_data() && sys_get_tick_ms() - gsm_sim_get_old_ms_received() > 50){
        
        char data_receive[512];
        memset(data_receive, 0, sizeof(data_receive));

        /*uint32_t data_len = */gsm_sim_get_new_data(data_receive);
        sq_push(&queue_data, data_receive);
        gsm_sim_clear_buffer();
        uart_send_string(UART_PORT, data_receive);
        //uart_send_string(UART_PORT, "end string \r\n");
    }
    if(!sq_is_empty(&queue_data)){
        //return;
	}
}



uint8_t power_on(void){

    static gsm_state state = PWR_GET_STATUS;
    static uint32_t old_tick_ms = 0;
    static uint32_t time_to_wait = 0;
    static uint8_t status = 0;

    if(sys_get_tick_ms() - old_tick_ms < time_to_wait){
        return 0;
    }

    old_tick_ms = sys_get_tick_ms();

    switch (state)
    {
    case PWR_GET_STATUS:

        uart_send_string(UART_PORT, "PWR GET STATUS\r\n");
        status = gsm_get_status();
        if(status == POWER_ON){
            state = PWR_OFF_STEP1;
            time_to_wait = 0;
            status = 0;
        }else{
            state = PWR_ON_STEP1;
            time_to_wait = 0;
        }
        break;
    
    case PWR_ON_STEP1:
        gsm_pull_down_pwr();
        time_to_wait = 1000;
        state = PWR_ON_STEP2;
        uart_send_string(UART_PORT, "PWR ON STEP 1\r\n");
        break;

    case PWR_ON_STEP2:
        gsm_pull_up_pwr();
        time_to_wait = 5000;
        state = PWR_WAIT_ON;
        uart_send_string(UART_PORT, "PWR ON STEP 2\r\n");
        //uart_send_byte(UART_PORT, state);
        break;

    case PWR_WAIT_ON:
        status = gsm_get_status();
        //uart_send_string(UART_PORT, "PWR_WAIT_ON\r\n");
        //uart_send_byte(UART_PORT, gsm_get_status());
        if(status == POWER_ON){
            state = PWR_GET_STATUS;
            uart_send_string(UART_PORT, "POWER ON\r\n");
            return 1;
        }
        break;

    case PWR_OFF_STEP1:
        gsm_pull_down_pwr();
        time_to_wait = 2500;
        state = PWR_OFF_STEP2;
        //uart_send_byte(UART_PORT, state);
        uart_send_string(UART_PORT, "PWR OFF STEP 1\r\n");
        break;

    case PWR_OFF_STEP2:
        gsm_pull_up_pwr();
        time_to_wait = 3000;
        state = PWR_WAIT_OFF;
        uart_send_string(UART_PORT, "PWR OFF STEP 2\r\n");
        //uart_send_byte(UART_PORT, state);
        break;

    case PWR_WAIT_OFF:
        //uart_send_string(UART_PORT, "PWR_WAIT_OFF\r\n");
        time_to_wait = 50;
        if(gsm_get_status() == POWER_OFF){
            state = PWR_ON_STEP1;
            uart_send_string(UART_PORT, "POWER OFF\r\n");
        }
        break;

    default:
        break;

    }
    return 0;
}

void loop(void){
    static uint8_t state_machine = POWER_ON;
    static uint8_t flag_sent = 0;
    
    switch (state_machine){
    case POWER_ON:
        if(power_on() == 1){
            state_machine = GSM_START;
        }
        break;

    case GSM_START:
        //uart_send_string(UART_PORT,"AT+CICCID=?\r");
        //gsm_sim_send_string("AT\r");
        if(send_command(m_list_command_startup)){
            state_machine = GSM_INIT;
        }             
        break;

    case GSM_INIT:
        if(!flag_sent && send_command(m_list_command_init)){
            flag_sent = 1;           
        }
        break;

    default:
        break;
    }
}

uint8_t send_command(uint8_t **command_list){
    static uint8_t **current_cmd = NULL;
    static uint32_t old_tick_ms = 0;
    static uint8_t is_init = 0;

    if (!is_init) {
        current_cmd = command_list;
        old_tick_ms = sys_get_tick_ms();
        is_init = 1;
    }

    if (*current_cmd == NULL) {
        is_init = 0; // Reset for next command list
        return 1;
    }

    if (sys_get_tick_ms() - old_tick_ms >= 3000) {
        gsm_sim_send_string((const char *)*current_cmd);
        //gsm_sim_send_string("\r\nTEST\r\n");
        uart_send_string(UART_PORT, "\r\nSend command:\r\n");
        current_cmd++;
        old_tick_ms = sys_get_tick_ms();
    }

    return 0;
}




