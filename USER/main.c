#include "stm32f10x.h" 
#include "SystemClock.h"
#include "Usart.h"
#include "stdio.h"
#include "Delay.h"
// Device header
void GPIO_Init();
int main(){
   	Stm32_Clock_Init(6);
		usart_init(72,115200);
	  delay_init(72);
		GPIO_Init();
		while(1){
		GPIOA->ODR&=~(1<<3);
		}
}
void GPIO_Init(){
	GPIOA->CRL|=3<<4*3;
}