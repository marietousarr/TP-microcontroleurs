#include "MyTimer.h"

MyTimer_Struct_TypeDef Timer;

int main (){
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ; 
	
	Timer.timer = TIM2;
	Timer.ARR = 360*4; // resolution
	Timer.PSC = 1;
	
	MyTimer_EncoderMode(&Timer);
	int k; // valeur pour calculer 'a
	int alpha;
	k = Timer.timer -> CNT;
	
	// calculer 'a à partir de k sacahnt que la resolution c'est arr
	alpha = k/4;
}
