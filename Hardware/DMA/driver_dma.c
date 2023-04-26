#include "driver_dma.h"
#include "driver_debug.h"

void DMA_Init(void)
{
    /*USART_DEBUG DMA*/
    dma_single_data_parameter_struct dma_init_struct;        
   	rcu_periph_clock_enable(DEBUG_DMA_RCU);													
  	
	dma_deinit(DEBUG_DMA,DEBUG_DMA_CH);		
	
	dma_init_struct.periph_addr 		= (uint32_t)&USART_DATA(DEBUG);             
   	dma_init_struct.periph_inc			= DMA_PERIPH_INCREASE_DISABLE;   
   	dma_init_struct.memory0_addr 		= (uint32_t)recv_buff;           
   	dma_init_struct.memory_inc 			= DMA_MEMORY_INCREASE_ENABLE;       
   	dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;         		
   	dma_init_struct.circular_mode 		= DMA_CIRCULAR_MODE_DISABLE;      	
   	dma_init_struct.direction 			= DMA_PERIPH_TO_MEMORY;          	          
   	dma_init_struct.number 				= DEBUG_RECEIVE_LENGTH;         	                     
   	dma_init_struct.priority			= DMA_PRIORITY_ULTRA_HIGH;  		

	dma_single_data_mode_init(DEBUG_DMA,DEBUG_DMA_CH,&dma_init_struct);
	
	dma_channel_subperipheral_select(DEBUG_DMA,DEBUG_DMA_CH,DMA_SUBPERI4);
	dma_channel_enable(DEBUG_DMA,DEBUG_DMA_CH);
	
	dma_interrupt_enable(DEBUG_DMA,DEBUG_DMA_CH,DMA_CHXCTL_FTFIE);
	nvic_irq_enable(DEBUG_DMA_CH_IRQ, 2, 1); 

    usart_dma_receive_config(DEBUG, USART_DENR_ENABLE);



    /*LVGL Framebuffer DMA*/
    dma_multi_data_parameter_struct dma_init_parameter;
    /* peripheral clock enable */
    rcu_periph_clock_enable(LVBUF_DMA_RCU);
    /* DMA peripheral configure */
    dma_deinit(LVBUF_DMA,LVBUF_DMA_CH);
    dma_init_parameter.periph_width = DMA_PERIPH_WIDTH_16BIT;
    dma_init_parameter.periph_inc = DMA_PERIPH_INCREASE_ENABLE;
    dma_init_parameter.memory_width = DMA_MEMORY_WIDTH_16BIT;
    dma_init_parameter.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_parameter.memory_burst_width = DMA_MEMORY_BURST_4_BEAT;
    dma_init_parameter.periph_burst_width = DMA_PERIPH_BURST_4_BEAT;
    dma_init_parameter.critical_value = DMA_FIFO_4_WORD;
    dma_init_parameter.circular_mode = DMA_CIRCULAR_MODE_DISABLE;
    dma_init_parameter.direction = DMA_MEMORY_TO_MEMORY;
    dma_init_parameter.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_multi_data_mode_init(LVBUF_DMA,LVBUF_DMA_CH,&dma_init_parameter);
    nvic_irq_enable(LVBUF_DMA_CH_IRQ, 0, 0);
}

void DEBUG_DMA_CH_IRQ_HANDLER(void)
{
    if(dma_interrupt_flag_get(DEBUG_DMA,DEBUG_DMA_CH,DMA_INT_FLAG_FTF) == SET)  // 传输完成中断 
	{	
	  dma_interrupt_flag_clear(DEBUG_DMA,DEBUG_DMA_CH,DMA_INT_FLAG_FTF);	    // 清中断标志位
		//recv_complete_flag = 1;                                             // 数据传输完成 
  	}
}
