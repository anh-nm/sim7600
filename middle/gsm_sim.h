#ifndef __GSM_SIM_H__
#define __GSM_SIM_H__

#include "systick.h"
#include "uart.h"
#include "string.h"

void init_gsm_sim(void);
void init_gsm_power_pin(void);
uint8_t gsm_get_status(void);
void gsm_pull_down_pwr(void);
void gsm_pull_up_pwr(void);
void gsm_sim_send_string(const char *str);

uint32_t gsm_sim_have_new_data(void);
uint32_t gsm_sim_get_old_ms_received(void);
uint32_t gsm_sim_get_new_data(char *out_buff);
void gsm_sim_clear_buffer(void);


#endif /*__GSM_SIM_H__*/
