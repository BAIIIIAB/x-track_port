#ifndef __DRIVER_KEY_H
#define __DRIVER_KEY_H

#define KEY_CLK                  RCU_GPIOA
#define KEY_PORT                 GPIOA
#define KEY_PIN                  GPIO_PIN_0

#define KEY_EXTI_IRQN			 EXTI0_IRQn
#define KEY_EXTI_PORT_SOURCE 	 EXTI_SOURCE_GPIOA
#define KEY_EXTI_PIN_SOURCE  	 EXTI_SOURCE_PIN0
#define KEY_EXTI_LINE 			 EXTI_0
#define KEY_EXTI_IRQHandler      EXTI0_IRQHandler

void KEY_Init(void);
void KEY_Scan(void);
#endif
