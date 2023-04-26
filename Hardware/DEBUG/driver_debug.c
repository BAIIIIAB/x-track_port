#include "driver_debug.h"
#include "driver_dma.h"

#include <stdio.h>

uint8_t  recv_buff[DEBUG_RECEIVE_LENGTH]; // 接收缓冲区
uint16_t recv_length;					  // 接收数据长度
uint8_t  recv_complete_flag; 

void Debug_Init(uint32_t baud_rate)
{
	rcu_periph_clock_enable(DEBUG_TX_CLK);
	rcu_periph_clock_enable(DEBUG_RX_CLK);
	rcu_periph_clock_enable(DEBUG_CLK);
	
    gpio_af_set(DEBUG_TX_PORT,DEBUG_AF,DEBUG_TX_PIN);	
	gpio_af_set(DEBUG_RX_PORT,DEBUG_AF,DEBUG_RX_PIN);	

	gpio_mode_set(DEBUG_TX_PORT,GPIO_MODE_AF,GPIO_PUPD_PULLUP,DEBUG_TX_PIN);
	gpio_mode_set(DEBUG_RX_PORT,GPIO_MODE_AF,GPIO_PUPD_PULLUP,DEBUG_RX_PIN);

	gpio_output_options_set(DEBUG_TX_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,DEBUG_TX_PIN);
	gpio_output_options_set(DEBUG_RX_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,DEBUG_RX_PIN);

	usart_deinit(DEBUG);
	usart_baudrate_set(DEBUG,baud_rate);
	usart_parity_config(DEBUG,USART_PM_NONE);
	usart_word_length_set(DEBUG,USART_WL_8BIT);
	usart_stop_bit_set(DEBUG,USART_STB_1BIT);

	usart_enable(DEBUG);
	usart_transmit_config(DEBUG,USART_TRANSMIT_ENABLE);
	usart_receive_config(DEBUG,USART_RECEIVE_ENABLE);
	
	nvic_irq_enable(DEBUG_IRQ, 2, 2);
    #if !USE_DEBUG_DMA
        usart_interrupt_enable(DEBUG,USART_INT_RBNE);//读数据缓冲区非空中断和过载错误中断
    #endif
	usart_interrupt_enable(DEBUG,USART_INT_IDLE);//IDlE线检测中断
    
}

void usart_send_data(uint8_t ucch)
{
	usart_data_transmit(DEBUG,(uint8_t)ucch);
	while(RESET == usart_flag_get(DEBUG,USART_FLAG_TBE));
}

void usart_send_string(uint8_t *ucstr)
{
	while(ucstr && *ucstr)
	{
	  usart_send_data(*ucstr++);
	}
}

int fputc(int ch, FILE *f)
{
     usart_send_data(ch);
     return ch;
}

void DEBUG_IRQHandler(void)
{
    #if !USE_DEBUG_DMA
    	if(usart_interrupt_flag_get(DEBUG,USART_INT_FLAG_RBNE) == SET)   // 接收缓冲区不为空
		{
			recv_buff[recv_length++] = usart_data_receive(DEBUG);      // 把接收到的数据放到缓冲区中
		}
	#endif
    if(usart_interrupt_flag_get(DEBUG,USART_INT_FLAG_IDLE) == SET)   // 检测到帧中断
	{
		usart_data_receive(DEBUG);                                     // 必须要读，读出来的值不能要
		#if USE_DEBUG_DMA
			recv_length = DEBUG_RECEIVE_LENGTH - dma_transfer_number_get(DEBUG_DMA, DEBUG_DMA_CH);																 // 数据接收完毕，数组结束标志
			dma_channel_disable(DEBUG_DMA, DEBUG_DMA_CH);
			DMA_Init();
		#endif
		recv_buff[recv_length] = '\0';
		recv_complete_flag = 1;                                          // 接收完成 
	}
}

