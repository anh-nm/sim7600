#include "systick.h"

static uint32_t msTick;

void init_systick(){
    //RCC_DeInit();
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/1000);
}

void SysTick_Handler(void){
    msTick ++;
}

uint32_t sys_get_tick_ms(){
    return msTick;
}


