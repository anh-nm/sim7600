#ifndef __LED_H__
#define __LED_H__

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "hardware_config.h"

void init_led();

void led_on();

void led_off();

#endif /*__LED_H__*/