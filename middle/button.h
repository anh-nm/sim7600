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
    LONG_CLICK = 4,
    HOLD_BUTTON = 5,
    HOLD_BUTTON_LONG,
    WAIT_CLICK
} button_state;

typedef enum {
    CLICK = 1,
    DOUBLE_CLICK = 2,
    TRIBLE_CLICK = 3
} time_click;
void init_button(void);
uint8_t get_btn_status(void);
uint8_t button_loop(void);

#endif /*__BUTTON_H__*/