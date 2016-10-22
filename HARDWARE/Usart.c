#include "stdio.h"
#include "Usart.h"
u8 USART_RX_BUF[USART_REC_LEN]; 
u16 USART_RX_STA=0; 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);  
	USART2->DR = (u8) ch;      	
	return ch;
}

void USART2_IRQHandler(void)
{
	u8 res;	
	if(USART2->SR&(1<<5))	
	{	 
		res=USART2->DR; 
		if((USART_RX_STA&0x8000)==0)
		{
			if(USART_RX_STA&0x4000)
			{
				if(res!=0x0a)USART_RX_STA=0;
				else USART_RX_STA|=0x8000;	
			}else 
			{	
				if(res==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=res;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;
				}		 
			}
		}  		 									     
	}
}
void usart_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);
	mantissa=temp;				 
	fraction=(temp-mantissa)*16; 	 
  mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;     
	RCC->APB1ENR|=1<<17;   
	GPIOA->CRL&=0XFFFF00FF;
	GPIOA->CRL|=0X00008B00; 
	RCC->APB2RSTR|=1<<14;   
	RCC->APB1RSTR&=~(1<<17);	   	   
 	USART2->BRR=mantissa; 
	USART2->CR1|=0X200C;  
	USART2->CR1|=1<<5;    	    	
	MY_NVIC_Init(3,3,USART2_IRQn,2);
}