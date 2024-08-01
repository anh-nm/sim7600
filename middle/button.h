#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "hardware_config.h"
//#include "systick.h"

#define BTN_ON             0
#define BTN_OFF            !BTN_ON

typedef enum {
    NO_CLICK = 0,
    CLICK,
    LONG_CLICK,
    HOLD_BUTTON,
    HOLD_BUTTON_LONG
} button_state;

void init_button(void);
uint8_t get_btn_status(void);
uint8_t button_loop(void);

#endif /*__BUTTON_H__*/