/*
 * power_on_gsm.h
 *
 *  Created on: Jul 26, 2024
 *      Author: MinhAnh
 */

#ifndef POWER_ON_GSM_H_
#define POWER_ON_GSM_H_

#include "gsm_sim.h"
#include "uart.h"
#include "struc_queue.h"

#define     POWER_ON    1
#define     POWER_OFF   0
#define     GSM_START   2
#define     GSM_INIT    3

typedef enum {
    PWR_GET_STATUS = 0,
    PWR_ON,
    PWR_OFF,
    PWR_ON_STEP1,
    PWR_ON_STEP2,
    PWR_WAIT_ON,
    PWR_OFF_STEP1,
    PWR_OFF_STEP2,
    PWR_WAIT_OFF
} gsm_state;

static uint8_t *m_list_command_startup[] = {
	/* Check Sim Availble */
	(uint8_t*)"AT\r",				/* Check sim availabel */
	(uint8_t*)"ATZ\r",
	(uint8_t*)"ATE0\r",				/* ATE0: Echo mode off */
	(uint8_t*)"ATH\r",				/* Ngat ket noi hien co */
	(uint8_t*)"AT+CFUN=1\r",		/* AT+CFUN: Dat chuc nang dien thoai
									   AT+CFUN=1 Toan bo chuc chuc nang */
	(uint8_t*)"AT+CMEE=2\r",		/* AT+CMEE: Bao loi thiet bi di dong
									   AT+CMEE=2 Enable +CME ERROR: <err> result code and use verbose <err> values */
	//(uint8_t*)"AT+CREG=1\r",		/* Network Registration */
	(uint8_t*)"AT+CREG?\r",			/* AT+CREG: Dang ky mang
									   AT+CREG? TA returns the status of result */
	//(uint8_t*)"AT+CGREG=1\r",		/* Enable Network Registration */
	//(uint8_t*)"AT+CGREG?\r",
	//(uint8_t*)"AT+CNUM\r",
	(uint8_t*)"AT+CLTS=1\r",		// Enable time local
	(uint8_t*)"AT+CCLK?\r",			// Get clock
	(uint8_t*)"AT+CPIN?\r",			// Get clock
	(uint8_t*)"AT+CICCID\r",			// Get clock
	NULL
};

static uint8_t *m_list_command_init[] = {
	/* Init Sim properties */
	(uint8_t*)"AT+CMGD=1,4\r",							/* Delete all messages */
	(uint8_t*)"AT+CMGF=1\r",							/* AT+CMGF: chon dinh dang cua tin nhan. 1 - Set SMS Text Mode */
    //(uint8_t*)"AT+CMGF?\r",								/* View SMS Text Mode */
    (uint8_t*)"AT+CPMS=\"SM\",\"SM\",\"SM\"\r", 		/* Select memory storages */
	(uint8_t*)"AT+CNMI=2,1\r",							/* Set SMS notification */
	(uint8_t*)"AT+CSMP=49,167,0,0\r\n",					//CMD_SET_SMS_TEXT_MODE_PARAM
    (uint8_t*)"AT+CSDH=1\r",							/* Set SMS notification */
//	(uint8_t*)"AT+CSCS=\"IRA\"\r",						//CMD_SET_TE_CHAR
	(uint8_t*)"AT+CSAS\r",								/* Save Setting SMS */
	NULL
};

// static uint8_t *m_list_http_init[] = {
// 	(uint8_t*)"AT+HTTPINIT\r",
// 	(uint8_t*)"AT+HTTPTERM\r",
// 	(uint8_t*)"AT+HTTP\r",
// 	NULL
// };

void gsm_data_receive(void);
uint8_t power_on(void);
uint8_t send_command(uint8_t **command_list);
void loop(void);

#endif /* POWER_ON_GSM_H_ */
