#include "SystemClock.h"
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset)	 
{ 	   	 
	SCB->VTOR = NVIC_VectTab|(Offset & (u32)0x1FFFFF80);
}

void MYRCC_DeInit(void)
{	
 	RCC->APB1RSTR = 0x00000000;		 
	RCC->APB2RSTR = 0x00000000; 
	RCC->AHBENR = 0x00000014;   
  RCC->APB2ENR = 0x00000000; 			   
  RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     	 															 
	RCC->CFGR &= 0xF8FF0000;   				 
	RCC->CR &= 0xFEF6FFFF;     
	RCC->CR &= 0xFFFBFFFF;     	   	  
	RCC->CFGR &= 0xFF80FFFF;    
	RCC->CIR = 0x00000000;     
	MY_NVIC_SetVectorTable(0x08000000,0x0);
}
void Stm32_Clock_Init(u8 PLL)
{
	unsigned char temp=0;   
	MYRCC_DeInit();		  
 	RCC->CR|=0x00010000;  
	while(!(RCC->CR>>17));
	RCC->CFGR=0X00000000; 
	PLL-=2;				  
	RCC->CFGR|=PLL<<18;   
	RCC->CFGR|=1<<16;	  
	FLASH->ACR|=0x32;	  
	RCC->CR|=0x01000000;  
	while(!(RCC->CR>>25));
	RCC->CFGR|=0x00000002;	 
	while(temp!=0x02)     
	{   
		temp=RCC->CFGR>>2;
		temp&=0x03;
	}    
}		