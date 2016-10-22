#ifndef __USART_H
#define __USART_H
#include "stm32f10x.h" 
#define USART_REC_LEN  			
extern u8  USART_RX_BUF[USART_REC_LEN]; 
extern u16 USART_RX_STA;
void usart_init(u32 pclk2,u32 bound);
#endif