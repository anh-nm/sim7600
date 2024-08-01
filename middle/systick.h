#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "stm32f4xx_it.h"

void init_systick();

uint32_t sys_get_tick_ms();

#endif /*__SYSTICK_H__*/
