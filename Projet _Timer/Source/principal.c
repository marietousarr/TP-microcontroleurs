#include "MyTimer.h"

int main(void)
{

RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
/* Test sans fonctions
TIM2->ARR = 9999;
TIM2->PSC = 1199;
TIM2->CR1 = TIM2->CR1 | ( 1 << 0);
	
	while(1) {
		if (TIM2->SR & TIM_SR_UIF) { // Scrutation de UIF
    TIM2->SR = TIM2->SR & ~TIM_SR_UIF; // Remise à zéro de UIF
		}
	}
*/
	
MyTimer_Struct_TypeDef Timer;
Timer.timer = TIM2;
Timer.ARR = 9999;
Timer.PSC = 1199;
MyTimer_Base_Init (&Timer );
	
MyTimer_Base_Start (&Timer);
while(1) 
	MyTimer_Base_Stop (&Timer);

}

