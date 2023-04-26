#ifndef __DRIVER_DEBUG_H
#define __DRIVER_DEBUG_H

#include "gd32f4xx.h"
#include "systick.h"

#define DEBUG_CLK       RCU_USART0
#define DEBUG_TX_CLK    RCU_GPIOA
#define DEBUG_RX_CLK    RCU_GPIOA

#define DEBUG_TX_PORT   GPIOA
#define DEBUG_TX_PIN    GPIO_PIN_9

#define DEBUG_RX_PORT   GPIOA
#define DEBUG_RX_PIN    GPIO_PIN_10

#define DEBUG_AF        GPIO_AF_7

#define DEBUG               USART0

#define DEBUG_IRQ           USART0_IRQn
#define DEBUG_IRQHandler    USART0_IRQHandler

#define DEBUG_RECEIVE_LENGTH    4096

/* 0：中断接收 1： DMA接收*/
#define USE_DEBUG_DMA 0


extern uint8_t  recv_buff[DEBUG_RECEIVE_LENGTH]; // 接收缓冲区
extern uint16_t recv_length;					 // 接收数据长度
extern uint8_t  recv_complete_flag; 

void Debug_Init(uint32_t baud_rate);
void usart_send_data(uint8_t ucch);
void usart_send_string(uint8_t *ucstr);

#endif