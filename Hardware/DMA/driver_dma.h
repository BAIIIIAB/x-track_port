#ifndef _driver_DMA_H
#define _driver_DMA_H

#include "gd32f4xx.h"
#include "systick.h"

/*USART0_RX DMA1_CH2*/
#define DEBUG_DMA_RCU                 RCU_DMA1
#define DEBUG_DMA                     DMA1
#define DEBUG_DMA_CH                  DMA_CH2
#define DEBUG_DMA_CH_IRQ              DMA1_Channel2_IRQn
#define DEBUG_DMA_CH_IRQ_HANDLER      DMA1_Channel2_IRQHandler

/*LVGL FrameBuffer DMA1_CH0 */
#define LVBUF_DMA_RCU                 RCU_DMA1
#define LVBUF_DMA                     DMA1
#define LVBUF_DMA_CH                  DMA_CH0
#define LVBUF_DMA_CH_IRQ              DMA1_Channel0_IRQn
#define LVBUF_DMA_CH_IRQHANDLER       DMA1_Channel0_IRQnHandler

void DMA_Init(void);

/*
	\brief dma transfer data
	\param[in] src_addr: source address
	\param[in] dst_addr: destination address
	\param[in] datalength: data length
	\param[out] none
	\retval none
*/
void dma_transfer(uint32_t src_addr, uint32_t dst_addr, uint32_t datalength);


#endif
