#include "led.h"

void init_led(){
    GPIO_InitTypeDef gpio;
    GPIO_StructInit(&gpio);
    gpio.GPIO_Pin = LED_PIN;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(LED_PORT, &gpio);
}

void led_on(){
    GPIO_SetBits(LED_PORT, LED_PIN);
}

void led_off(){
    GPIO_ResetBits(LED_PORT, LED_PIN);
}