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

void DMA_Init(void);

#endif
