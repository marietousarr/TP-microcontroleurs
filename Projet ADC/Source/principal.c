//#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"


int main(void)
{
	
RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ; //on a écrit 1 au 2e, 3e et 4e bit de APB2ENR
	
 

while(1);
}
