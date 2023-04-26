#ifndef _DRIVER_LED_H
#define _DRIVER_LED_H

#include "gd32f4xx.h"
#include "systick.h"
#include "gd32f4xx_gpio.h"

#define BIT_ADDR(byte_offset, bitnum)   (volatile unsigned long *)(0x42000000 + (byte_offset * 32) + (bitnum * 4))
#define GPIOD_OCTL_OFFSET               ((GPIOD + 0x14) - 0x40000000)
#define PDout(n)                        *(BIT_ADDR(GPIOD_OCTL_OFFSET, n))

#define LED1_CLK        RCU_GPIOE
#define LED1_PORT       GPIOE
#define LED1_PIN        GPIO_PIN_3

#define LED2_CLK        RCU_GPIOD
#define LED2_PORT       GPIOD
#define LED2_PIN        GPIO_PIN_7

#define LED3_CLK        RCU_GPIOG
#define LED3_PORT       GPIOG
#define LED3_PIN        GPIO_PIN_3

#define LED4_CLK        RCU_GPIOA
#define LED4_PORT       GPIOA
#define LED4_PIN        GPIO_PIN_5

void LED_Init(void);

void LED1_ON();
void LED1_OFF();
void LED2_ON();
void LED2_OFF();
void LED3_ON();
void LED3_OFF();
void LED4_ON();
void LED4_OFF();

#endif
