#include "led.h"

void LED_Init(void)
{
    rcu_periph_clock_enable(LED1_CLK);
    rcu_periph_clock_enable(LED2_CLK);
    rcu_periph_clock_enable(LED3_CLK);
    rcu_periph_clock_enable(LED4_CLK);
    
    gpio_mode_set(LED1_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED1_PIN);
    gpio_mode_set(LED2_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED2_PIN);
    gpio_mode_set(LED3_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED3_PIN);
    gpio_mode_set(LED4_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED4_PIN);
    
    gpio_output_options_set(LED1_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LED1_PIN);
    gpio_output_options_set(LED2_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LED2_PIN);
    gpio_output_options_set(LED3_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LED3_PIN);
    gpio_output_options_set(LED4_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LED4_PIN);
    
    gpio_bit_reset(LED1_PORT, LED1_PIN);
    gpio_bit_reset(LED2_PORT, LED2_PIN);
    gpio_bit_reset(LED3_PORT, LED3_PIN);
    gpio_bit_reset(LED4_PORT, LED4_PIN);
}

void LED1_ON()
{
    gpio_bit_set(LED1_PORT, LED1_PIN);
}

void LED1_OFF()
{
    gpio_bit_reset(LED1_PORT, LED1_PIN);
}

void LED2_ON()
{
    gpio_bit_set(LED2_PORT, LED2_PIN);
}

void LED2_OFF()
{
    gpio_bit_reset(LED2_PORT, LED2_PIN);
}

void LED3_ON()
{
    gpio_bit_set(LED3_PORT, LED3_PIN);
}

void LED3_OFF()
{
    gpio_bit_reset(LED3_PORT, LED3_PIN);
}

void LED4_ON()
{
    gpio_bit_set(LED4_PORT, LED4_PIN);
}

void LED4_OFF()
{
    gpio_bit_reset(LED4_PORT, LED4_PIN);
}
