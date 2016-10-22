#ifndef __SystemClock_H
#define __SystemClock_H
#include "stm32f10x.h" 
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);
void MYRCC_DeInit(void);
void Stm32_Clock_Init(u8 PLL);
#endif