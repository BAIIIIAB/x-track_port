#include "key.h"
#include "led.h"

#include <stdio.h>

void KEY_Init(void)
{
    rcu_periph_clock_enable(KEY_CLK);
    gpio_mode_set(KEY_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, KEY_PIN);

    rcu_periph_clock_enable(RCU_SYSCFG);
    nvic_irq_enable(KEY_EXTI_IRQN,3u,3u);
    syscfg_exti_line_config(KEY_EXTI_PORT_SOURCE, KEY_EXTI_PIN_SOURCE);
    exti_init(KEY_EXTI_LINE, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
    
    exti_interrupt_enable(KEY_EXTI_LINE);
    exti_interrupt_flag_clear(KEY_EXTI_LINE);
}

void KEY_EXTI_IRQHandler(void)
{
    if(exti_interrupt_flag_get(KEY_EXTI_LINE) == SET)
    {
        if(gpio_input_bit_get(KEY_PORT, KEY_PIN) == SET)
        {
            gpio_bit_toggle(LED2_PORT, LED2_PIN);
            printf("key pressed\r\n");
        }
        else
        {
            printf("key released\r\n");
        }
        exti_interrupt_flag_clear(KEY_EXTI_LINE);
    }

}

void KEY_Scan(void)
{
    if(gpio_input_bit_get(KEY_PORT, KEY_PIN) == SET)
    {
        delay_1ms(20);
        if(gpio_input_bit_get(KEY_PORT, KEY_PIN) == SET)
        {
            gpio_bit_toggle(LED2_PORT, LED2_PIN);
            printf("key pressed\r\n");
            while(gpio_input_bit_get(KEY_PORT,KEY_PIN) == SET);
            printf("key released\r\n");
        }
    }
}
