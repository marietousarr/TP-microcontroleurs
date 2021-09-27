#include "MyTimer.h"
#include <stdio.h>

void (*pFnc) (void) = NULL;
void (* IT_function) (void);

void TIM1_UP_IRQHandler(){
		TIM1->SR = TIM1->SR & ~TIM_SR_UIF;
	
		if (pFnc != NULL)
			(*pFnc) ();
}


void TIM2_IRQHandler(){
	TIM2->SR = TIM2->SR & ~TIM_SR_UIF;
	
		if (pFnc != NULL)
			(*pFnc) ();
}


void TIM3_IRQHandler(){
	TIM3->SR = TIM3->SR & ~TIM_SR_UIF;
	
		if (pFnc != NULL)
			(*pFnc) ();
}


void TIM4_IRQHandler(){
	TIM4->SR = TIM4->SR & ~TIM_SR_UIF;
	
		if (pFnc != NULL)
			(*pFnc) ();
}


void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ){
	Timer -> timer -> ARR = Timer ->ARR;
	Timer -> timer -> PSC = Timer ->PSC;
}

void MyTimer_ActiveIT(TIM_TypeDef* Timer ,char Prio, void (*IT_function) (void)){
	
	//Timer -> DIER = Timer -> DIER | (1 << 0);
	//Timer -> CR1 = Timer -> CR1 | TIM1_CR1_CEN;
	Timer -> DIER = TIM_DIER_UIE;
	
	if (Timer == TIM1){ 
		NVIC_EnableIRQ(TIM1_UP_IRQn);
		NVIC_SetPriority(TIM1_UP_IRQn, (int)Prio);
	}else if (Timer == TIM2){
		NVIC_EnableIRQ(TIM2_IRQn);
		NVIC_SetPriority(TIM2_IRQn, (int)Prio);
	}else if (Timer == TIM3){
		NVIC_EnableIRQ(TIM3_IRQn);
		NVIC_SetPriority(TIM3_IRQn, (int)Prio);
	}else if (Timer == TIM4){
		NVIC_EnableIRQ(TIM4_IRQn);
		NVIC_SetPriority(TIM4_IRQn, (int)Prio);
	}
	
	pFnc = IT_function;
	
}

void MyTimer_PWM(TIM_TypeDef* Timer ,char Channel ){
	
	//mode 1 PWM
	Timer -> CCMR1 = Timer -> CCMR1 | (1 <<6);
	Timer -> CCMR1 = Timer -> CCMR1 | (1 <<5);
	Timer -> CCMR1 = Timer -> CCMR1 & ~(1 <<4);
	
	Timer -> CCMR1 = Timer -> CCMR1 & ~(1 <<0);
	Timer -> CCMR1 = Timer -> CCMR1 & ~(1 <<1);

	

	Timer -> CCMR1 = Timer -> CCMR1 | (1 <<3);
	Timer -> CR1 = Timer -> CR1 | (1 <<7);
	
	Timer -> EGR = Timer -> EGR | (1 <<0);

	Timer -> CCER = Timer -> CCER & ~(1<<1); // CC1P
	Timer -> CCER = Timer -> CCER | (1<<0); //CC1E
	Timer -> CCER = Timer -> CCER | (1<<2); //CC1EN

	Timer -> BDTR = Timer -> BDTR | (1<<15); //moe
	Timer -> BDTR = Timer -> BDTR | (1<<10); //ossi
	Timer -> BDTR = Timer -> BDTR | (1<<11); //ossR

	// edge aligned mode 
	Timer -> CR1 = Timer -> CR1 & ~(1 << 6); // CMS edge aligned mode 
	Timer -> CR1 = Timer -> CR1 & ~(1 << 5); // CMS
}

void PWMRatio(TIM_TypeDef* Timer ,int ration){
	int valeur = ration * (Timer -> ARR) /100;
	Timer -> CCR1 = 	valeur;
}

