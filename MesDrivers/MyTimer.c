#include "MyTimer.h"


void TIM1_UP_IRQHandler(){
	
}

void TIM2_IRQHandler(){
	TIM2->SR = TIM2-> SR & ~(1<<0);
	
	GPIOA -> ODR = GPIOA -> ODR | (1<<5);
	
}
void TIM3_IRQHandler(){
	TIM3-> SR &= ~(1<<0);
}
void TIM4_IRQHandler(){
	TIM4-> SR &= ~(1<<0);
}
void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ){
	Timer -> timer -> ARR = Timer ->ARR;
	Timer -> timer -> PSC = Timer ->PSC;
}

void MyTimer_ActiveIT(TIM_TypeDef* Timer ,char Prio ){
	
	//Timer -> DIER = Timer -> DIER | (1 << 0);
	//Timer -> CR1 = Timer -> CR1 | TIM1_CR1_CEN;
	Timer -> DIER = TIM_DIER_UIE;
	
	if (Timer == TIM1){ 
		NVIC_EnableIRQ(TIM1_UP_IRQn);

	}else if (Timer == TIM2){
		NVIC_EnableIRQ(TIM2_IRQn);
	}else if (Timer == TIM3){
		NVIC_EnableIRQ(TIM3_IRQn);
	}else if (Timer == TIM4){
		NVIC_EnableIRQ(TIM4_IRQn);
	}
	
	// priorité
	//NVIC_SetPriority(iter, (int)Prio);
}
